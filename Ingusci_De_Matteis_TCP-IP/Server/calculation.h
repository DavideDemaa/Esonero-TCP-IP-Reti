/*
 *      calculation.h
 *      Author: Paolo Ingusci - De Matteis Davide
 */

#include <stdio.h>
#include <string.h>
#include<ctype.h>
#include <stdlib.h>
#ifndef NULL
#define NULL   ((void *) 0)
#endif

//server
int set_operation(char *str, int *n1, int *n2, char *op); //function that sets operand and operator
float calculation(int n1, int n2, char op); //function that performs a specific operation based on the operand
float add(int a, int b); //adds the two operands
float sub(int a, int b); //subtracts the two operands
float mult(int a, int b); //multiplication of the two operands
float division(int a, int b); //division of the two operands
