#ifndef _MAIL_PARSED_V2_H_
#define _MAIL_PARSED_V2_H_

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct parsed_string_t {
		int len;
		char *pdata;
	} parsed_string ;

	struct parsed_message_info_s {
		struct parsed_string_t header_from;
		struct parsed_string_t header_to;
		struct parsed_string_t header_cc;
		struct parsed_string_t header_bcc;
		struct parsed_string_t header_subject;
		struct parsed_string_t header_spf;
		struct parsed_string_t body;
	};

	void init_parse(struct parsed_message_info_s *parsed_mail_info);
	void clean_parse(struct parsed_message_info_s *parsed_mail_info);
	int parse_mail_for_file(char *email, struct parsed_message_info_s *parsed_mail_info);

#ifdef __cplusplus
}
#endif


#endif
