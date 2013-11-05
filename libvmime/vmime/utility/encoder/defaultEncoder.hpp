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

#ifndef VMIME_UTILITY_ENCODER_DEFAULTENCODER_HPP_INCLUDED
#define VMIME_UTILITY_ENCODER_DEFAULTENCODER_HPP_INCLUDED


#include "vmime/utility/encoder/encoder.hpp"


namespace vmime {
namespace utility {
namespace encoder {


/** Default encoder (simple copy, no encoding/decoding is performed).
  */

class defaultEncoder : public encoder
{
public:

	defaultEncoder();

	utility::stream::size_type encode(utility::inputStream& in, utility::outputStream& out, utility::progressListener* progress = NULL);
	utility::stream::size_type decode(utility::inputStream& in, utility::outputStream& out, utility::progressListener* progress = NULL);
};


} // encoder
} // utility
} // vmime


#endif // VMIME_UTILITY_ENCODER_DEFAULTENCODER_HPP_INCLUDED
