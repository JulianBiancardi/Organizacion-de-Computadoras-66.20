#include "args_parser.h"

#include <stdbool.h>
/*
#include <errno.h>*/
#include <getopt.h>
/*#include <limits.h>*/
#include <stdio.h>
#include <stdlib.h>

#include "constantsTP2.h"

#define END -2

int static read_args(int argc, char** argv, file_reader_t* output,
                     unsigned int* cs, unsigned int* w, unsigned int* bs);
void static print_version();
void static print_help();
int static get_output_file(FILE** output_file, char* optarg);
int static validate_nums(unsigned long int x, unsigned long int y);

int get_arguments(int argc, char** argv, file_reader_t* file_reader,
                  unsigned int* cs, unsigned int* w, unsigned int* bs) {
  if (read_args(argc, argv, file_reader, cs, w, bs) != NO_ERROR) {
    return ERROR;
  }
  return NO_ERROR;
}

int static read_args(int argc, char** argv, file_reader_t* file_reader,
                     unsigned int* cs, unsigned int* w, unsigned int* bs) {
  static struct option arguments[] = {{"version", no_argument, NULL, 'V'},
                                      {"help", no_argument, NULL, 'h'},
                                      {"output", required_argument, NULL, 'o'},
                                      {"ways", no_argument, NULL, 'w'},
                                      {"cachesize", no_argument, NULL, 'c'},
                                      {"blocksize", no_argument, NULL, 'b'},
                                      {NULL, 0, NULL, 0}};
  while (true) {
    int opt = getopt_long(argc, argv, "hVo:w:c:b:", arguments, NULL);
    if (opt == -1) {
      break;
    }
    switch (opt) {
      case 'h':
        print_help();
        return END;
      case 'V':
        print_version();
        return END;
      case 'o':
        break;
      case 'w':
        *w = (unsigned int)strtol(optarg, NULL, 10);
        break;
      case 'c':
        *cs = (unsigned int)strtol(optarg, NULL, 10);
        break;
      case 'b':
        *bs = (unsigned int)strtol(optarg, NULL, 10);
        break;
      default:
        print_help();
        return ERROR;
    }
  }

  return NO_ERROR;
}

void static print_version() { printf("Version: %d\n", VERSION); }

void static print_help() {
  printf("Usage:\n\n");

  printf("\ttp2 -h\n");
  printf("\ttp2 -V\n");
  printf("\ttp2 options archivo\n");

  printf("\nOptions:\n\n");

  printf("\t-h, --help\t\tPrint usage information.\n");
  printf("\t-V, --version\t\tPrints version information.\n");
  printf("\t-o, --output\t\tPath to output file.\n");
  printf("\t-w, --ways\t\tAmount of ways.\n");
  printf("\t-c --cachesize\t\tSize of the cache in kilobytes.\n");
  printf("\t-b --blocksize\t\tSize of a block in bytes.\n");

  printf("\nExamples:\n\n");

  printf("\ttp2 -w 4 -cs 8 -bs 16 prueba1.mem\n");
}

int static get_output_file(FILE** output_file, char* optarg) {
  if (strncmp(optarg, "-", 1) == 0) {
    *output_file = stdout;
  } else {
    *output_file = fopen(optarg, "w");
    if (*output_file == NULL) {
      return ERROR;
    }
  }
  return NO_ERROR;
}
