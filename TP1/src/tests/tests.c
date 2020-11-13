#include "args_parser_tests.h"
#include "mcd_tests.h"
#include "mcm_tests.h"

int main(int argc, char** argv) {
  mcd_tests();
  mcm_tests();
  args_parser_tests();
}