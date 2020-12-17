#include "args_parser.h"

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantsTP2.h"

int static read_args(int argc, char** argv, file_writer_t* file_writer,
                     unsigned int* cs, unsigned int* w, unsigned int* bs);
void static print_version();
void static print_help();
int static get_input_file(int argc, char** argv, file_reader_t* file_reader);

int get_arguments(int argc, char** argv, file_reader_t* file_reader,
                  file_writer_t* file_writer, unsigned int* cs, unsigned int* w,
                  unsigned int* bs) {
  if (read_args(argc, argv, file_writer, cs, w, bs) != NO_ERROR) {
    return ERROR;
  }

  if (get_input_file(argc, argv, file_reader) != NO_ERROR) {
    return ERROR;
  }

  return NO_ERROR;
}

int static read_args(int argc, char** argv, file_writer_t* file_writer,
                     unsigned int* cachesize, unsigned int* ways,
                     unsigned int* blocksize) {
  static struct option arguments[] = {
      {"version", no_argument, NULL, 'V'},
      {"help", no_argument, NULL, 'h'},
      {"output", required_argument, NULL, 'o'},
      {"ways", required_argument, NULL, 'w'},
      {"cachesize", required_argument, NULL, 'c'},
      {"blocksize", required_argument, NULL, 'b'},
      {NULL, 0, NULL, 0}};

  bool bs = false;
  bool cs = false;
  bool w = false;

  while (true) {
    int opt = getopt_long(argc, argv, "hVo:w:c:b:", arguments, NULL);
    if (opt == -1) {
      break;
    }
    switch (opt) {
      case 'h':
        print_help();
        return ERROR;
      case 'V':
        print_version();
        return ERROR;
      case 'o':
        file_writer_open(file_writer, optarg);
        break;
      case 'w':
        *ways = (unsigned int)strtoul(optarg, (char**)NULL, 10);
        w = true;
        break;
      case 'c':
        *cachesize = (unsigned int)strtoul(optarg, (char**)NULL, 10);
        cs = true;
        break;
      case 'b':
        *blocksize = (unsigned int)strtoul(optarg, (char**)NULL, 10);
        bs = true;
        break;
      default:
        print_help();
        return ERROR;
    }
  }

  if (!w || !cs || !bs) {
    fprintf(stderr, "Command Error: missing parameters.\n");
    print_help();
    return ERROR;
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

int static get_input_file(int argc, char** argv, file_reader_t* file_reader) {
  if (argc > optind + 1) {
    fprintf(stderr, "Command Error: Too many arguments provided.\n");
    print_help();
    return ERROR;
  }
  if (argc == optind) {
    fprintf(stderr, "Command Error: Too few arguments provided.\n");
    print_help();
    return ERROR;
  }
  file_reader_open(file_reader, argv[optind]);
  return NO_ERROR;
}