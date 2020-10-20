#include "args_parser.h"

#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"

void static print_version();
void static print_help();

void get_arguments(int argc, char** argv, char* input_file, char* output_file,
                   bool* encode) {
  static struct option arguments[] = {{"version", no_argument, NULL, 'V'},
                                      {"help", no_argument, NULL, 'h'},
                                      {"input", required_argument, NULL, 'i'},
                                      {"output", required_argument, NULL, 'o'},
                                      {"decode", no_argument, NULL, 'd'},
                                      {NULL, 0, NULL, 0}};

  *encode = false;

  while (true) {
    int opt = getopt(argc, argv, "Vhiod");
    if (opt == -1) {
      break;
    }
    switch (opt) {
      case 'V':
        print_version();
        exit(0);
        break;
      case 'h':
        print_help();
        exit(0);
        break;
      case 'o':
        strncpy(output_file, optarg, sizeof(char) * FILE_NAME_MAX_LEN);
        break;
      case 'i':
        strncpy(output_file, optarg, sizeof(char) * FILE_NAME_MAX_LEN);
        break;
      case 'd':
        *encode = true;
        break;
      default:
        print_help();
        exit(-1);
    }
  }
}

void static print_version() { printf("Version: %d", VERSION); }

void static print_help() {
  printf("Usage:\n\n");

  printf("\ttp0 -h\n");
  printf("\ttp0 -V\n");
  printf("\ttp0 [options]\n");

  printf("Options:\n\n");

  printf("\t-V, --version\t\tPrint version and quit.\n");
  printf("\t-h, --help\t\tPrint this information.\n");
  printf("\t-o, --output\t\tPath to output file.\n");
  printf("\t-i, --input\t\tPath to input file.\n");
  printf("\t-d, --decode\t\tDecode a base64-encoded file.\n");

  printf("Examples:\n\n");

  printf("\ttp0 -i input.txt -o output.txt\n");
}