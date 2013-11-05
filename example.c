#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "mailparse.h"

void usage(char *prog)
{
	printf("%s [option]\n", prog);
	printf("-f:		email file\n");
	printf("-h:		help\n");
	exit(0);
}

int main (int argc, char **argv)
{
	char eml_file[1024] = {0};

	// ----------------
	int ch;
	const char *args = "f:h";
	while ((ch = getopt(argc, argv, args)) != -1) {
		switch (ch) {
			case 'f':
				snprintf(eml_file, sizeof(eml_file), "%s", optarg);
				break;
			case 'h':
			default:
				usage(argv[0]);
				break;	
		}
	}
	if (*eml_file == '\0') {
		usage(argv[0]);
	}


	int ret = 0;
	struct parsed_message_info_s parsed_mail_info;

	init_parse(&parsed_mail_info);

	ret = parse_mail_for_file(eml_file, &parsed_mail_info);
	if (ret > 0) {
		fprintf(stderr, "parse email fail\n");
		return 0;
	}

	printf("------------------------------------\n");
	printf("from: [%d]%s\n", parsed_mail_info.header_from.len, parsed_mail_info.header_from.pdata);
	printf("to: [%d]%s\n", parsed_mail_info.header_to.len, parsed_mail_info.header_to.pdata);
	printf("cc: [%d]%s\n", parsed_mail_info.header_cc.len, parsed_mail_info.header_cc.pdata);
	printf("bcc: [%d]%s\n", parsed_mail_info.header_bcc.len, parsed_mail_info.header_bcc.pdata);
	printf("subject: [%d]%s\n", parsed_mail_info.header_subject.len, parsed_mail_info.header_subject.pdata);
	printf("\n");
	printf("body: [%d]\n%s\n", parsed_mail_info.body.len, parsed_mail_info.body.pdata);
	printf("------------------------------------\n");

	clean_parse(&parsed_mail_info);

	return 0;

}

