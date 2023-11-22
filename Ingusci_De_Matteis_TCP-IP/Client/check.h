/*
 *      check.h
 *      Author: Paolo Ingusci - De Matteis Davide
 */
//client check.h

#include <stdio.h>
#include <string.h>
#include<ctype.h>
#define MAX 64
#ifndef NULL
#define NULL   ((void *) 0)
#endif

int string_check(const char *str); //function that contains string check
int lenght_check(int leng); //function that checks that the maximum length of the entered string is 64 characters
int operator_check(char *str); //function that checks that the first character entered is a string
int num_check(char *str); //function that verifies that the two operands have been inserted in the string



