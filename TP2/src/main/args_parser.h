#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include "file_reader.h"

/* Receives argc and argv and processes the command to make a decision.
 * If an output file is selected, it is put into output_file.
 * If the program was signaled to calculate the mcd, then divisor is true.
 * Otherwise, it is set to false.
 *
 * If the arguments are correct and the program must end, -2 is returned.
 * If an argument is invalid or not recognized, -1 is returned.
 * If the arguments are valid and the program can continue, 0 is returned.
 */
int get_arguments(int argc, char** argv, file_reader_t* file_reader,
                  unsigned int* cs, unsigned int* w, unsigned int* bs);

#endif
