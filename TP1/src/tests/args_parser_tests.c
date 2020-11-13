#define _POSIX_C_SOURCE 200112L
#include "args_parser_tests.h"

#include <stdio.h>
#include <unistd.h>

#include "../main/args_parser.h"
#include "tests_setup.h"

#define NO_ERROR 0
#define ERROR -1

int static single_arg_command_test();
int static two_args_command_test();
int static three_args_command_test();
int static four_args_command_test();
int static five_args_command_test();
int static valid_huge_number_command_test();
int static invalid_huge_number_command_test();
int static negative_number_command_test();
int static number_zero_command_test();
int static number_one_command_test();
int static number_two_command_test();
int static output_file_option_command_test();

void args_parser_tests() {
  begin_tests("ArgsParser");

  int old_stderr = dup(fileno(stderr));
  freopen("/dev/null", "w", stderr);

  print_test("Commands with a single argument returns an error",
             single_arg_command_test, ERROR);
  print_test("Commands with two arguments returns an error",
             two_args_command_test, ERROR);
  print_test("Commands with three arguments returns an error",
             three_args_command_test, ERROR);
  print_test("Commands with four arguments returns an error",
             four_args_command_test, ERROR);
  print_test("Commands with five arguments are valid", five_args_command_test,
             NO_ERROR);
  print_test("Commands with huge valid numbers are valid",
             valid_huge_number_command_test, NO_ERROR);
  print_test("Commands with huge invalid numbers return error",
             invalid_huge_number_command_test, ERROR);
  print_test("Commands with negative numbers return error",
             negative_number_command_test, ERROR);
  print_test("Commands with number zero return error", number_zero_command_test,
             ERROR);
  print_test("Commands with number one return error", number_one_command_test,
             ERROR);
  print_test("Commands with number two are valid", number_two_command_test,
             NO_ERROR);
  print_test("Commands with specified output file are valid",
             output_file_option_command_test, NO_ERROR);

  fclose(stderr);
  stderr = fdopen(old_stderr, "w");

  end_tests();
}

int static single_arg_command_test() {
  int argc = 1;
  char* argv[] = {"./common"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}

int static two_args_command_test() {
  int argc = 2;
  char* argv[] = {"./common", "-o"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}

int static three_args_command_test() {
  int argc = 3;
  char* argv[] = {"./common", "-o", "-"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}

int static four_args_command_test() {
  int argc = 4;
  char* argv[] = {"./common", "-o", "-", "40"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}

int static five_args_command_test() {
  int argc = 5;
  char* argv[] = {"./common", "-o", "-", "40", "5"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}

int static valid_huge_number_command_test() {
  int argc = 5;
  char* argv[] = {"./common", "-o", "-", "4294967295", "5"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}

int static invalid_huge_number_command_test() {
  int argc = 5;
  char* argv[] = {"./common", "-o", "-", "4294967296", "5"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}

int static negative_number_command_test() {
  int argc = 5;
  char* argv[] = {"./common", "-o", "-", "-40", "5"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}

int static number_zero_command_test() {
  int argc = 5;
  char* argv[] = {"./common", "-o", "-", "0", "5"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}

int static number_one_command_test() {
  int argc = 5;
  char* argv[] = {"./common", "-o", "-", "1", "5"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}

int static number_two_command_test() {
  int argc = 5;
  char* argv[] = {"./common", "-o", "-", "2", "5"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}

int static output_file_option_command_test() {
  int argc = 5;
  char* argv[] = {"./common", "-o", "tests_file_output.txt", "40", "5"};
  FILE* output;
  unsigned int x, y;
  bool mcm_bool, mcd_bool;

  int old_stdout = dup(fileno(stdout));
  freopen("/dev/null", "w", stdout);
  int result = get_arguments(argc, argv, &output, &x, &y, &mcm_bool, &mcd_bool);
  fclose(stdout);
  stdout = fdopen(old_stdout, "w");
  return result;
}