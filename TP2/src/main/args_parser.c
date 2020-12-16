#include "args_parser.h"
/*
#include <errno.h>
#include <getopt.h>
#include <limits.h>*/
#include <stdio.h>
/*#include <stdlib.h>
#include <string.h>*/

#include "constantsTP2.h"

int static read_args(int argc, char** argv, FILE** output, unsigned int* cs,
                     unsigned int* w, unsigned int* bs);
void static print_version();
void static print_help();
int static get_output_file(FILE** output_file, char* optarg);
int static validate_mcm_mcd(bool* mcm, bool* mcd);
int static get_nums(int argc, char** argv, unsigned int* x, unsigned int* y);
int static validate_nums(unsigned long int x, unsigned long int y);

int get_arguments(int argc, char** argv, file_reader_t* file_reader,
                  unsigned int* cs, unsigned int* w, unsigned int* bs) {
  if (read_args(argc, argv, file_reader, cs, w, bs) == ERROR) {
    return ERROR;
  }

  if (validate_mcm_mcd(mcm, mcd) == ERROR) {
    return ERROR;
  }

  return get_nums(argc, argv, x, y);
}

int static read_args(int argc, char** argv, file_reader_t* file_reader,
                     unsigned int* cs, unsigned int* w, unsigned int* bs) {
  static struct option arguments[] = {{"version", no_argument, NULL, 'V'},
                                      {"help", no_argument, NULL, 'h'},
                                      {"output", required_argument, NULL, 'o'},
                                      {"divide", no_argument, NULL, 'd'},
                                      {"multiple", no_argument, NULL, 'm'},
                                      {NULL, 0, NULL, 0}};
  while (true) {
    int opt = getopt_long(argc, argv, "hVo:dm", arguments, NULL);
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
        if (get_output_file(output, optarg) == ERROR) {
          return ERROR;
        }
        break;
      case 'd':
        *mcm = false;
        break;
      case 'm':
        *mcd = false;
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
  printf("\t-cs --cachesize\t\tSize of the cache in kilobytes.\n");
  printf("\t-bs --blocksize\t\tSize of a block in bytes.\n");

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

int static validate_mcm_mcd(bool* mcm, bool* mcd) {
  if (!(*mcm || *mcd)) {  // If both are false
    fprintf(stderr,
            "Command Error: -m and -d are not allowed simultaneously.\n");
    print_help();
    return ERROR;
  }
  return NO_ERROR;
}

int static get_nums(int argc, char** argv, unsigned int* x, unsigned int* y) {
  if (argc < 5) {
    fprintf(stderr, "Command Error: Too few arguments passed.\n");
    print_help();
    return ERROR;
  } else if (argc == 5) {
    long _x = strtol(argv[3], (char**)NULL, 10);
    long _y = strtol(argv[4], (char**)NULL, 10);
    if (validate_nums(_x, _y) == ERROR) {
      return ERROR;
    }
    *x = _x;
    *y = _y;
  } else if (argc == 6) {
    long _x = strtol(argv[4], (char**)NULL, 10);
    long _y = strtol(argv[5], (char**)NULL, 10);
    if (validate_nums(_x, _y) == ERROR) {
      return ERROR;
    }
    *x = _x;
    *y = _y;
  } else {
    fprintf(stderr, "Command Error: Too many arguments passed.\n");
    print_help();
    return ERROR;
  }
  return NO_ERROR;
}

int static validate_nums(unsigned long x, unsigned long y) {
  if (x > UINT_MAX || y > UINT_MAX || errno == ERANGE) {
    fprintf(stderr,
            "Command Error: The number entered is too big.\nPlease, enter "
            "numbers between 2 and 4294967295\n");
    return ERROR;
  }
  if (x < 2 || y < 2) {
    fprintf(stderr,
            "Command Error: The number entered is too small.\nPlease, enter "
            "numbers between 2 and 4294967295\n");
    return ERROR;
  }
  return NO_ERROR;
}