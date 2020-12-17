#ifndef TESTS_SETUP_H
#define TESTS_SETUP_H

#define ERROR -1
#define NO_ERROR 0

void print_test(char* message, int (*func)(), int expected_value);
void begin_tests(char* module_tested);
void end_tests();

#endif