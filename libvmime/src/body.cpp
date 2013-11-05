//
// VMime library (http://www.vmime.org)
// Copyright (C) 2002-2009 Vincent Richard <vincent@vincent-richard.net>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 3 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// Linking this library statically or dynamically with other modules is making
// a combined work based on this library.  Thus, the terms and conditions of
// the GNU General Public License cover the whole combination.
//

#include "vmime/bodyPart.hpp"
#include "vmime/body.hpp"

#include "vmime/options.hpp"

#include "vmime/contentTypeField.hpp"
#include "vmime/text.hpp"

#include "vmime/utility/random.hpp"

#include "vmime/parserHelpers.hpp"

#include "vmime/emptyContentHandler.hpp"
#include "vmime/stringContentHandler.hpp"


namespace vmime
{


body::body()
	: m_contents(create <emptyContentHandler>()), m_part(NULL), m_header(NULL)
{
}


body::~body()
{
}


void body::parse(const string& buffer, const string::size_type position,
	const string::size_type end, string::size_type* newPosition)
{
	removeAllParts();

	// Check whether the body is a MIME-multipart
	bool isMultipart = false;
	string boundary;

	try
	{
		const ref <const contentTypeField> ctf =
			m_header.acquire()->findField(fields::CONTENT_TYPE).dynamicCast <contentTypeField>();

		const mediaType type = *ctf->getValue().dynamicCast <const mediaType>();

		if (type.getType() == mediaTypes::MULTIPART)
		{
			isMultipart = true;

			try
			{
				boundary = ctf->getBoundary();
			}
			catch (exceptions::no_such_parameter&)
			{
				// No "boundary" parameter specified: we can try to
				// guess it by scanning the body contents...
				string::size_type pos = buffer.find("\n--", position);

				if ((pos != string::npos) && (pos < end))
				{
					pos += 3;

					const string::size_type start = pos;

					char_t c = buffer[pos];
					string::size_type length = 0;

					// We have to stop after a reasonnably long boundary length (100)
					// not to take the whole body contents for a boundary...
					while (pos < end && length < 100 && !(c == '\r' || c == '\n'))
					{
						++length;
						c = buffer[pos++];
					}

					if (pos < end && length < 100)
					{
						// RFC #1521, Page 31:
						// "...the boundary parameter, which consists of 1 to 70
						//  characters from a set of characters known to be very
						//  robust through email gateways, and NOT ending with
						//  white space..."
						while (pos != start && parserHelpers::isSpace(buffer[pos - 1]))
							--pos;

						boundary = string(buffer.begin() + start,
						                  buffer.begin() + pos);
					}
				}
			}
		}
 	}
	catch (exceptions::no_such_field&)
	{
		// No "Content-Type" field...
	}

	// This is a multi-part body
	if (isMultipart && !boundary.empty())
	{
		const string boundarySep("--" + boundary);

		string::size_type partStart = position;
		string::size_type pos = buffer.find(boundarySep, position);

		bool lastPart = false;

		if (pos != string::npos && pos < end)
		{
			m_prologText = string(buffer.begin() + position, buffer.begin() + pos);
		}

		for (int index = 0 ; !lastPart && (pos != string::npos) && (pos < end) ; ++index)
		{
			string::size_type partEnd = pos;

			// Get rid of the [CR]LF just before the boundary string
			if (pos >= (position + 1) && buffer[pos - 1] == '\n') --partEnd;
			if (pos >= (position + 2) && buffer[pos - 2] == '\r') --partEnd;

			// Check whether it is the last part (boundary terminated by "--")
			pos += boundarySep.length();

			if (pos + 1 < end && buffer[pos] == '-' && buffer[pos + 1] == '-')
			{
				lastPart = true;
				pos += 2;
			}

			// RFC #1521, Page 31:
			// "...(If a boundary appears to end with white space, the
			//  white space must be presumed to have been added by a
			//  gateway, and must be deleted.)..."
			while (pos < end && (buffer[pos] == ' ' || buffer[pos] == '\t'))
				++pos;

			// End of boundary line
			if (pos + 1 < end && buffer[pos] == '\r' && buffer[pos + 1] =='\n')
			{
				pos += 2;
			}
			else if (pos < end && buffer[pos] == '\n')
			{
				++pos;
			}

			if (index > 0)
			{
				ref <bodyPart> part = vmime::create <bodyPart>();

				part->parse(buffer, partStart, partEnd, NULL);
				part->m_parent = m_part;

				m_parts.push_back(part);
			}

			partStart = pos;
			pos = buffer.find(boundarySep, partStart);
		}

		m_contents = vmime::create <emptyContentHandler>();

		// Last part was not found: recover from missing boundary
		if (!lastPart && pos == string::npos)
		{
			ref <bodyPart> part = vmime::create <bodyPart>();

			try
			{
				part->parse(buffer, partStart, end);
			}
			catch (std::exception&)
			{
				throw;
			}

			part->m_parent = m_part;

			m_parts.push_back(part);
		}
		// Treat remaining text as epilog
		else if (partStart < end)
		{
			m_epilogText = string(buffer.begin() + partStart, buffer.begin() + end);
		}
	}
	// Treat the contents as 'simple' data
	else
	{
		encoding enc;

		try
		{
			const ref <const headerField> cef =
				m_header.acquire()->findField(fields::CONTENT_TRANSFER_ENCODING);

			enc = *cef->getValue().dynamicCast <const encoding>();
		}
		catch (exceptions::no_such_field&)
		{
			// Defaults to "7bit" (RFC-1521)
			enc = vmime::encoding(encodingTypes::SEVEN_BIT);

			// Set header field
			m_header.acquire()->ContentTransferEncoding()->setValue(enc);
		}

		// Extract the (encoded) contents
		m_contents = vmime::create <stringContentHandler>(buffer, position, end, enc);
	}

	setParsedBounds(position, end);

	if (newPosition)
		*newPosition = end;
}


void body::generate(utility::outputStream& os, const string::size_type maxLineLength,
	const string::size_type /* curLinePos */, string::size_type* newLinePos) const
{
	// MIME-Multipart
	if (getPartCount() != 0)
	{
		string boundary;

		if (m_header.acquire() == NULL)
		{
			boundary = generateRandomBoundaryString();
		}
		else
		{
			try
			{
				ref <const contentTypeField> ctf =
					m_header.acquire()->findField(fields::CONTENT_TYPE)
						.dynamicCast <const contentTypeField>();

				boundary = ctf->getBoundary();
			}
			catch (exceptions::no_such_field&)
			{
				// Warning: no content-type and no boundary string specified!
				boundary = generateRandomBoundaryString();
			}
			catch (exceptions::no_such_parameter&)
			{
				// Warning: no boundary string specified!
				boundary = generateRandomBoundaryString();
			}
		}

		const string& prologText =
			m_prologText.empty()
				? (isRootPart()
					? options::getInstance()->multipart.getPrologText()
					: NULL_STRING
				  )
				: m_prologText;

		const string& epilogText =
			m_epilogText.empty()
				? (isRootPart()
					? options::getInstance()->multipart.getEpilogText()
					: NULL_STRING
				  )
				: m_epilogText;

		if (!prologText.empty())
		{
			text prolog(word(prologText, getCharset()));

			prolog.encodeAndFold(os, maxLineLength, 0,
				NULL, text::FORCE_NO_ENCODING | text::NO_NEW_LINE_SEQUENCE);

			os << CRLF;
		}

		os << "--" << boundary;

		for (int p = 0 ; p < getPartCount() ; ++p)
		{
			os << CRLF;

			getPartAt(p)->generate(os, maxLineLength, 0);

			os << CRLF << "--" << boundary;
		}

		os << "--" << CRLF;

		if (!epilogText.empty())
		{
			text epilog(word(epilogText, getCharset()));

			epilog.encodeAndFold(os, maxLineLength, 0,
				NULL, text::FORCE_NO_ENCODING | text::NO_NEW_LINE_SEQUENCE);

			os << CRLF;
		}

		if (newLinePos)
			*newLinePos = 0;
	}
	// Simple body
	else
	{
		// Generate the contents
		m_contents->generate(os, getEncoding(), maxLineLength);
	}
}


/*
   RFC #1521, Page 32:
   7.2.1. Multipart: The common syntax

   "...Encapsulation boundaries must not appear within the
   encapsulations, and must be no longer than 70 characters..."


   boundary := 0*69<bchars> bcharsnospace

   bchars := bcharsnospace / " "

   bcharsnospace :=    DIGIT / ALPHA / "'" / "(" / ")" / "+" /"_"
                 / "," / "-" / "." / "/" / ":" / "=" / "?"
*/

const string body::generateRandomBoundaryString()
{
	// 64 characters that can be _safely_ used in a boundary string
	static const char bchars[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-+";

	/*
		RFC #1521, Page 19:

		Since the hyphen character ("-") is represented as itself in the
		Quoted-Printable encoding, care must be taken, when encapsulating a
		quoted-printable encoded body in a multipart entity, to ensure that
		the encapsulation boundary does not appear anywhere in the encoded
		body.  (A good strategy is to choose a boundary that includes a
		character sequence such as "=_" which can never appear in a quoted-
		printable body.  See the definition of multipart messages later in
		this document.)
	*/

	string::value_type boundary[2 + 48 + 1] = { 0 };

	boundary[0] = '=';
	boundary[1] = '_';

	// Generate a string of random characters
	unsigned int r = utility::random::getTime();
	unsigned int m = sizeof(unsigned int);

	for (size_t i = 2 ; i < (sizeof(boundary) / sizeof(boundary[0]) - 1) ; ++i)
	{
			boundary[i] = bchars[r & 63];
			r >>= 6;

			if (--m == 0)
			{
				r = utility::random::getNext();
				m = sizeof(unsigned int);
			}
	}

	return (string(boundary));
}


bool body::isValidBoundary(const string& boundary)
{
	static const string validChars("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'()+_,-./:=?");

	const string::const_iterator end = boundary.end();
	bool valid = false;

	if (boundary.length() > 0 && boundary.length() < 70)
	{
		const string::value_type last = *(end - 1);

		if (!(last == ' ' || last == '\t' || last == '\n'))
		{
			valid = true;

			for (string::const_iterator i = boundary.begin() ; valid && i != end ; ++i)
				valid = (validChars.find_first_of(*i) != string::npos);
		}
	}

	return (valid);
}


//
// Quick-access functions
//


void body::setContentType(const mediaType& type, const charset& chset)
{
	ref <contentTypeField> ctf = m_header.acquire()->ContentType().dynamicCast <contentTypeField>();

	ctf->setValue(type);
	ctf->setCharset(chset);
}


void body::setContentType(const mediaType& type)
{
	m_header.acquire()->ContentType()->setValue(type);
}


const mediaType body::getContentType() const
{
	try
	{
		ref <const contentTypeField> ctf =
			m_header.acquire()->findField(fields::CONTENT_TYPE).dynamicCast <const contentTypeField>();

		return (*ctf->getValue().dynamicCast <const mediaType>());
	}
	catch (exceptions::no_such_field&)
	{
		// Defaults to "text/plain" (RFC-1521)
		return (mediaType(mediaTypes::TEXT, mediaTypes::TEXT_PLAIN));
	}
}


void body::setCharset(const charset& chset)
{
	// If a Content-Type field exists, set charset
	try
	{
		ref <contentTypeField> ctf =
			m_header.acquire()->findField(fields::CONTENT_TYPE).dynamicCast <contentTypeField>();

		ctf->setCharset(chset);
	}
	// Else, create a new Content-Type field of default type "text/plain"
	// and set charset on it
	catch (exceptions::no_such_field&)
	{
		setContentType(mediaType(mediaTypes::TEXT, mediaTypes::TEXT_PLAIN), chset);
	}
}


const charset body::getCharset() const
{
	try
	{
		const ref <const contentTypeField> ctf =
			m_header.acquire()->findField(fields::CONTENT_TYPE).dynamicCast <contentTypeField>();

		return (ctf->getCharset());
	}
	catch (exceptions::no_such_parameter&)
	{
		// Defaults to "us-ascii" (RFC-1521)
		return (vmime::charset(charsets::US_ASCII));
	}
	catch (exceptions::no_such_field&)
	{
		// Defaults to "us-ascii" (RFC-1521)
		return (vmime::charset(charsets::US_ASCII));
	}
}


void body::setEncoding(const encoding& enc)
{
	m_header.acquire()->ContentTransferEncoding()->setValue(enc);
}


const encoding body::getEncoding() const
{
	try
	{
		const ref <const headerField> cef =
			m_header.acquire()->findField(fields::CONTENT_TRANSFER_ENCODING);

		return (*cef->getValue().dynamicCast <const encoding>());
	}
	catch (exceptions::no_such_field&)
	{
		if (m_contents->isEncoded())
		{
			return m_contents->getEncoding();
		}
		else
		{
			// Defaults to "7bit" (RFC-1521)
			return vmime::encoding(encodingTypes::SEVEN_BIT);
		}
	}
}


void body::setParentPart(ref <bodyPart> parent)
{
	m_part = parent;
	m_header = (parent != NULL ? parent->getHeader() : NULL);
}


bool body::isRootPart() const
{
	ref <const bodyPart> part = m_part.acquire();
	return (part == NULL || part->getParentPart() == NULL);
}


ref <component> body::clone() const
{
	ref <body> bdy = vmime::create <body>();

	bdy->copyFrom(*this);

	return (bdy);
}


void body::copyFrom(const component& other)
{
	const body& bdy = dynamic_cast <const body&>(other);

	m_prologText = bdy.m_prologText;
	m_epilogText = bdy.m_epilogText;

	m_contents = bdy.m_contents;

	removeAllParts();

	for (int p = 0 ; p < bdy.getPartCount() ; ++p)
	{
		ref <bodyPart> part = bdy.getPartAt(p)->clone().dynamicCast <bodyPart>();

		part->m_parent = m_part;

		m_parts.push_back(part);
	}
}


body& body::operator=(const body& other)
{
	copyFrom(other);
	return (*this);
}


const string& body::getPrologText() const
{
	return (m_prologText);
}


void body::setPrologText(const string& prologText)
{
	m_prologText = prologText;
}


const string& body::getEpilogText() const
{
	return (m_epilogText);
}


void body::setEpilogText(const string& epilogText)
{
	m_epilogText = epilogText;
}


const ref <const contentHandler> body::getContents() const
{
	return (m_contents);
}


void body::setContents(ref <const contentHandler> contents)
{
	m_contents = contents;
}


void body::setContents(ref <const contentHandler> contents, const mediaType& type)
{
	m_contents = contents;

	setContentType(type);
}


void body::setContents(ref <const contentHandler> contents, const mediaType& type, const charset& chset)
{
	m_contents = contents;

	setContentType(type, chset);
}


void body::setContents(ref <const contentHandler> contents, const mediaType& type,
	const charset& chset, const encoding& enc)
{
	m_contents = contents;

	setContentType(type, chset);
	setEncoding(enc);
}


void body::initNewPart(ref <bodyPart> part)
{
	part->m_parent = m_part;

	ref <header> hdr = m_header.acquire();

	if (hdr != NULL)
	{
		// Check whether we have a boundary string
		try
		{
			ref <contentTypeField> ctf =
				hdr->findField(fields::CONTENT_TYPE).dynamicCast <contentTypeField>();

			try
			{
				const string boundary = ctf->getBoundary();

				if (boundary.empty() || !isValidBoundary(boundary))
					ctf->setBoundary(generateRandomBoundaryString());
			}
			catch (exceptions::no_such_parameter&)
			{
				// No "boundary" parameter: generate a random one.
				ctf->setBoundary(generateRandomBoundaryString());
			}

			if (ctf->getValue().dynamicCast <const mediaType>()->getType() != mediaTypes::MULTIPART)
			{
				// Warning: multi-part body but the Content-Type is
				// not specified as "multipart/..."
			}
		}
		catch (exceptions::no_such_field&)
		{
			// No "Content-Type" field: create a new one and generate
			// a random boundary string.
			ref <contentTypeField> ctf =
				hdr->getField(fields::CONTENT_TYPE).dynamicCast <contentTypeField>();

			ctf->setValue(mediaType(mediaTypes::MULTIPART, mediaTypes::MULTIPART_MIXED));
			ctf->setBoundary(generateRandomBoundaryString());
		}
	}
}


void body::appendPart(ref <bodyPart> part)
{
	initNewPart(part);

	m_parts.push_back(part);
}


void body::insertPartBefore(ref <bodyPart> beforePart, ref <bodyPart> part)
{
	initNewPart(part);

	const std::vector <ref <bodyPart> >::iterator it = std::find
		(m_parts.begin(), m_parts.end(), beforePart);

	if (it == m_parts.end())
		throw exceptions::no_such_part();

	m_parts.insert(it, part);
}


void body::insertPartBefore(const int pos, ref <bodyPart> part)
{
	initNewPart(part);

	m_parts.insert(m_parts.begin() + pos, part);
}


void body::insertPartAfter(ref <bodyPart> afterPart, ref <bodyPart> part)
{
	initNewPart(part);

	const std::vector <ref <bodyPart> >::iterator it = std::find
		(m_parts.begin(), m_parts.end(), afterPart);

	if (it == m_parts.end())
		throw exceptions::no_such_part();

	m_parts.insert(it + 1, part);
}


void body::insertPartAfter(const int pos, ref <bodyPart> part)
{
	initNewPart(part);

	m_parts.insert(m_parts.begin() + pos + 1, part);
}


void body::removePart(ref <bodyPart> part)
{
	const std::vector <ref <bodyPart> >::iterator it = std::find
		(m_parts.begin(), m_parts.end(), part);

	if (it == m_parts.end())
		throw exceptions::no_such_part();

	m_parts.erase(it);
}


void body::removePart(const int pos)
{
	m_parts.erase(m_parts.begin() + pos);
}


void body::removeAllParts()
{
	m_parts.clear();
}


int body::getPartCount() const
{
	return (m_parts.size());
}


bool body::isEmpty() const
{
	return (m_parts.size() == 0);
}


ref <bodyPart> body::getPartAt(const int pos)
{
	return (m_parts[pos]);
}


const ref <const bodyPart> body::getPartAt(const int pos) const
{
	return (m_parts[pos]);
}


const std::vector <ref <const bodyPart> > body::getPartList() const
{
	std::vector <ref <const bodyPart> > list;

	list.reserve(m_parts.size());

	for (std::vector <ref <bodyPart> >::const_iterator it = m_parts.begin() ;
	     it != m_parts.end() ; ++it)
	{
		list.push_back(*it);
	}

	return (list);
}


const std::vector <ref <bodyPart> > body::getPartList()
{
	return (m_parts);
}


const std::vector <ref <const component> > body::getChildComponents() const
{
	std::vector <ref <const component> > list;

	copy_vector(m_parts, list);

	return (list);
}


} // vmime
