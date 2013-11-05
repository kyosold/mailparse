#include <string>
#include <iostream>
#include <fstream>

#include <vmime/vmime.hpp>
#include <vmime/platforms/posix/posixHandler.hpp>

#include <string.h>
#include "mailparse.h"

using namespace std;


vmime::ref <vmime::message> init_mimeparse(char *email_file)
{
	try {
		// set platform
		vmime::platform::setHandler<vmime::platforms::posix::posixHandler>();

		std::ifstream file;
		file.open(email_file, std::ios::in | std::ios::binary);

		vmime::utility::inputStreamAdapter is(file);

		vmime::string data;
		vmime::utility::outputStreamStringAdapter os(data);

		vmime::utility::bufferedStreamCopy(is, os);

		// Actually parse the message
		vmime::ref <vmime::message> msg = vmime::create <vmime::message>();
		msg->parse(data);
	
		return msg;
	} catch (vmime::exception &e) {
		// std::cerr << e;
	} catch (std::exception &e) {
		// std::cerr << e.what();
	}

	return NULL;
}


int get_attachment_count(vmime::ref <vmime::message> msg)
{
	try {
		vmime::messageParser mp(msg);
		return mp.getAttachmentCount();	
	} catch (vmime::exception &e) {
	} catch (std::exception &e) {
	}

	return -1;
}


string get_header_for_name(vmime::ref <vmime::header> hdr, string name)
{
	try {
		string header_value;

		// Now, you can extract some of its components
		vmime::charset ch(vmime::charsets::UTF_8);

		if (hdr->hasField(name)) {
			if ((strcasecmp(name.c_str(), "to") == 0) 
				|| (strcasecmp(name.c_str(), "cc") == 0)
				|| (strcasecmp(name.c_str(), "bcc") == 0)) {	// addresslist

				vmime::ref<vmime::mailboxList> mailbox_list;
				if (strcasecmp(name.c_str(), "to") == 0) {	
					mailbox_list =  hdr->To()->getValue().dynamicCast<vmime::addressList>()->toMailboxList();
				} else if (strcasecmp(name.c_str(), "cc") == 0) {	
					mailbox_list =  hdr->Cc()->getValue().dynamicCast<vmime::addressList>()->toMailboxList();
				} else if (strcasecmp(name.c_str(), "bcc") == 0) {	
					mailbox_list =  hdr->Bcc()->getValue().dynamicCast<vmime::addressList>()->toMailboxList();
				}

				for (int i=0; i<mailbox_list->getMailboxCount(); i++) {
					// get name before email
					// cc_str += mailbox_list->getMailboxAt(i)->getName().getConvertedText(ch);

					// get value of email
					header_value += mailbox_list->getMailboxAt(i)->getEmail();
					header_value += " ";	
				}

				return header_value;

			} else if ((strcasecmp(name.c_str(), "from") == 0)
				|| (strcasecmp(name.c_str(), "sender") == 0)
				|| (strcasecmp(name.c_str(), "reply-to") == 0)
				|| (strcasecmp(name.c_str(), "delivered-to") == 0)) { // mailbox
			
				if (strcasecmp(name.c_str(), "from") == 0) {
					return hdr->From()->getValue().dynamicCast<vmime::mailbox>()->getEmail();
				} else if (strcasecmp(name.c_str(), "sender") == 0) {
					return hdr->Sender()->getValue().dynamicCast<vmime::mailbox>()->getEmail();
				} else if (strcasecmp(name.c_str(), "reply-to") == 0) {
					return hdr->ReplyTo()->getValue().dynamicCast<vmime::mailbox>()->getEmail();
				} else if (strcasecmp(name.c_str(), "delivered-to") == 0) {
					return hdr->DeliveredTo()->getValue().dynamicCast<vmime::mailbox>()->getEmail();
				}

			} else {	// text
				vmime::ref<vmime::headerField> hdr_hf = hdr->getField(name);
				return hdr_hf->getValue().dynamicCast<vmime::text>()->getConvertedText(ch);
			}
		}	
	} catch (vmime::exception &e) {
	} catch (std::exception &e) {
	}

	return "";
}


string get_parsed_body(vmime::ref <vmime::message> msg)
{
	try {
		vmime::messageParser mp(msg);

		string parsed_body;

		for (int i=0; i< mp.getTextPartCount(); ++i) {
			vmime::ref<const vmime::textPart> tp = mp.getTextPartAt(i);

			// text/html
			if (tp->getType().getSubType() == vmime::mediaTypes::TEXT_HTML) {
				vmime::ref<const vmime::htmlTextPart> htp = 
					tp.dynamicCast<const vmime::htmlTextPart>();

				//std::cout << "Length: " << htp->getText()->getLength() << std::endl;

				// HTML text is in tp->getText()
				// Plain text is in tp->getPlainText()
		   
				vmime::string htmlContents;
				vmime::utility::outputStreamStringAdapter htmlOut(htmlContents);
				vmime::utility::charsetFilteredOutputStream utf8Out(htp->getCharset(), vmime::charset("utf-8"), htmlOut); // 强制转换正文为utf8编码
				htp->getText()->extract(utf8Out);
				utf8Out.flush();

				// append parsed_body
				parsed_body += htmlContents;
			} else if (tp->getType().getSubType() == vmime::mediaTypes::TEXT_PLAIN) {
				vmime::ref<const vmime::plainTextPart> ptp =
					tp.dynamicCast<const vmime::plainTextPart>();

				vmime::string plainTextContent;
				vmime::utility::outputStreamStringAdapter plainOut(plainTextContent);
				vmime::utility::charsetFilteredOutputStream utf8Out(ptp->getCharset(), vmime::charset("utf-8"), plainOut);
				ptp->getText()->extract(utf8Out);
				utf8Out.flush();

				parsed_body += plainTextContent;
			} else {
				// nothing to do
			}
		}

		return parsed_body;
	} catch (vmime::exception &e) {
	} catch (std::exception &e) {
	} 

	return "";
}


void init_parse(struct parsed_message_info_s *parsed_mail_info)
{
	parsed_mail_info->header_from.len = 0;	
	parsed_mail_info->header_from.pdata = NULL;	

	parsed_mail_info->header_to.len = 0;	
	parsed_mail_info->header_to.pdata = NULL;	

	parsed_mail_info->header_cc.len = 0;	
	parsed_mail_info->header_cc.pdata = NULL;	

	parsed_mail_info->header_bcc.len = 0;	
	parsed_mail_info->header_bcc.pdata = NULL;	

	parsed_mail_info->header_subject.len = 0;	
	parsed_mail_info->header_subject.pdata = NULL;	

	parsed_mail_info->body.len = 0;	
	parsed_mail_info->body.pdata = NULL;	
}


void clean_parse(struct parsed_message_info_s *parsed_mail_info)
{
	if (parsed_mail_info->header_from.pdata != NULL) {
		free(parsed_mail_info->header_from.pdata);
		parsed_mail_info->header_from.pdata = NULL;

		parsed_mail_info->header_from.len = 0;
	}

    if (parsed_mail_info->header_to.pdata != NULL) {
        free(parsed_mail_info->header_to.pdata);
        parsed_mail_info->header_to.pdata = NULL;

        parsed_mail_info->header_to.len = 0;
    }  

    if (parsed_mail_info->header_cc.pdata != NULL) {
        free(parsed_mail_info->header_cc.pdata);
        parsed_mail_info->header_cc.pdata = NULL;

        parsed_mail_info->header_cc.len = 0;
    }  

    if (parsed_mail_info->header_bcc.pdata != NULL) {
        free(parsed_mail_info->header_bcc.pdata);
        parsed_mail_info->header_bcc.pdata = NULL;

        parsed_mail_info->header_bcc.len = 0;
    }  

    if (parsed_mail_info->header_subject.pdata != NULL) {
        free(parsed_mail_info->header_subject.pdata);
        parsed_mail_info->header_subject.pdata = NULL;

        parsed_mail_info->header_subject.len = 0;
    }  

    if (parsed_mail_info->body.pdata != NULL) {
        free(parsed_mail_info->body.pdata);
        parsed_mail_info->body.pdata = NULL;

        parsed_mail_info->body.len = 0;
    }  
}

int parse_mail_for_file(char *email, struct parsed_message_info_s *parsed_mail_info)
{
	vmime::ref <vmime::message> msg = init_mimeparse(email);	
	if (msg == NULL) {
		return 1;
	}

	vmime::ref <vmime::header> hdr = msg->getHeader();

	// get header from, to, cc, bcc ------------------------
	string from = get_header_for_name(hdr, "from");
	if (from.length() > 0) {
		parsed_mail_info->header_from.pdata = (char *)calloc(1, from.length() + 1);
		if (parsed_mail_info->header_from.pdata != NULL) {
			parsed_mail_info->header_from.len = from.length();

			memcpy(parsed_mail_info->header_from.pdata, from.c_str(), parsed_mail_info->header_from.len);
			parsed_mail_info->header_from.pdata[parsed_mail_info->header_from.len] = '\0';
		}
	}

	string to = get_header_for_name(hdr, "to");
	if (to.length() > 0) {
		parsed_mail_info->header_to.pdata = (char *)calloc(1, to.length() + 1);
		if (parsed_mail_info->header_to.pdata != NULL) {
			parsed_mail_info->header_to.len = to.length();

			memcpy(parsed_mail_info->header_to.pdata, to.c_str(), parsed_mail_info->header_to.len);
			parsed_mail_info->header_to.pdata[parsed_mail_info->header_to.len] = '\0';
		}
	}

	string cc = get_header_for_name(hdr, "cc");
	if (cc.length() > 0) {
		parsed_mail_info->header_cc.pdata = (char *)calloc(1, cc.length() + 1);
		if (parsed_mail_info->header_cc.pdata != NULL) {
			parsed_mail_info->header_cc.len = cc.length();

			memcpy(parsed_mail_info->header_cc.pdata, cc.c_str(), parsed_mail_info->header_cc.len);
			parsed_mail_info->header_cc.pdata[parsed_mail_info->header_cc.len] = '\0';
		}
	}
	
	string bcc = get_header_for_name(hdr, "bcc");
	if (bcc.length() > 0) {
		parsed_mail_info->header_bcc.pdata = (char *)calloc(1, bcc.length() + 1);
		if (parsed_mail_info->header_bcc.pdata != NULL) {
			parsed_mail_info->header_bcc.len = bcc.length();

			memcpy(parsed_mail_info->header_bcc.pdata, bcc.c_str(), parsed_mail_info->header_bcc.len);
			parsed_mail_info->header_bcc.pdata[parsed_mail_info->header_bcc.len] = '\0';
		}
	}

	string spf = get_header_for_name(hdr, "received-spf");
	if (spf.length() > 0) {
		parsed_mail_info->header_spf.pdata = (char *)calloc(1, spf.length() + 1);
		if (parsed_mail_info->header_spf.pdata != NULL) {
			parsed_mail_info->header_spf.len = spf.length();

			memcpy(parsed_mail_info->header_spf.pdata, spf.c_str(), parsed_mail_info->header_spf.len);
			parsed_mail_info->header_spf.pdata[parsed_mail_info->header_spf.len] = '\0';
		}
	}

	string subject = get_header_for_name(hdr, "subject");
	if (subject.length() > 0) {
		parsed_mail_info->header_subject.pdata = (char *)calloc(1, subject.length() + 1);
		if (parsed_mail_info->header_subject.pdata != NULL) {
			parsed_mail_info->header_subject.len = subject.length();

			memcpy(parsed_mail_info->header_subject.pdata, subject.c_str(), parsed_mail_info->header_subject.len);
			parsed_mail_info->header_subject.pdata[parsed_mail_info->header_subject.len] = '\0';
		}
	}

	// get body ----------------------
	string body = get_parsed_body(msg);
	if (body.length() > 0) {
		parsed_mail_info->body.pdata = (char *)calloc(1, body.length() + 1);
		if (parsed_mail_info->body.pdata != NULL) {
			parsed_mail_info->body.len = body.length();

			memcpy(parsed_mail_info->body.pdata, body.c_str(), parsed_mail_info->body.len);
			parsed_mail_info->body.pdata[parsed_mail_info->body.len] = '\0';
		}
	}

	return 0;
}

