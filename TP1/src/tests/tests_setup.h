#ifndef TESTS_SETUP_H
#define TESTS_SETUP_H

void print_test(char* message, int (*func)(), int expected_value);
void benchmark_test(char* message, int (*func)());
void begin_tests(char* module_tested);
void end_tests();

#endif