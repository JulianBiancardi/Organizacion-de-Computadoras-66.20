#include "args_parser.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

void static print_version();
void static print_help();

void get_arguments(int argc, char** argv, char* output_file, bool* divisor) {
  static struct option arguments[] = {{"version", no_argument, NULL, 'V'},
                                      {"help", no_argument, NULL, 'h'},
                                      {"output", required_argument, NULL, 'o'},
                                      {"decode", no_argument, NULL, 'd'},
                                      {"multiple", no_argument, NULL, 'm'},
                                      {NULL, 0, NULL, 0}};

  *divisor = false;  // False unless found

  while (true) {
    int opt = getopt_long(argc, argv, "hVo:dm", arguments, NULL);
    if (opt == -1) {
      break;
    }
    switch (opt) {
      case 'h':
        print_help();
        exit(0);
        break;
      case 'V':
        print_version();
        exit(0);
        break;
      case 'o':
        strncpy(output_file, optarg, sizeof(char) * FILE_NAME_MAX_LEN);
        break;
      case 'd':
        *divisor = true;
        break;
      case 'm':
        //.............................................
        break;
      default:
        print_help();
        exit(0);
    }
  }
}

void static print_version() { printf("Version: %d\n", VERSION); }

void static print_help() {
  printf("Usage:\n\n");

  printf("\tcommon -h\n");
  printf("\tcommon -V\n");
  printf("\tcommon [options] M N\n");

  printf("\nOptions:\n\n");

  printf("\t-h, --help\t\tPrint usage information.\n");
  printf("\t-V, --version\t\tPrints version information.\n");
  printf("\t-o, --output\t\tPath to output file.\n");
  printf("\t-d --divisor\t\tJust the divisor.\n");
  printf("\t-m --multiple\t\tJust the multiple.\n");

  printf("\nExamples:\n\n");

  printf("\tcommon -o - 256 192\n");
}