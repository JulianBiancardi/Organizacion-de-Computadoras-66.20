#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <stdbool.h>

/* Receives argc and argv and processes the command to make a decision.
 * If an input file is selected, it is put into input_file.
 * If an output file is selected, it is put into output_file.
 * If the program was signaled to encode, then encode is true.
 * Otherwise, it is set to false.
 *
 * If an argument of the command is not recognized, the program will be
 * terminated during the call of this function with an error code -1.
 */
void get_arguments(int argc, char** argv, char* input_file, char* output_file,
                   bool* encode);

#endif