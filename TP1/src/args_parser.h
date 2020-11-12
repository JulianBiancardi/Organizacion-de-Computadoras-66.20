#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <stdbool.h>
#include <stdio.h>

/* Receives argc and argv and processes the command to make a decision.
 * If an output file is selected, it is put into output_file.
 * If the program was signaled to calculate the mcd, then divisor is true.
 * Otherwise, it is set to false.
 *
 * If an argument of the command is not recognized, the program will be
 * terminated during the call of this function with an error code -1.
 */
int get_arguments(int argc, char** argv, FILE** output, unsigned int* x,
                  unsigned int* y, bool* mcm, bool* mcd);

#endif