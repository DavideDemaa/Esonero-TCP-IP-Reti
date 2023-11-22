/*
 *       calculation.c
 *      Author: Paolo Ingusci - De Matteis Davide
 */

#include "calculation.h"

int set_operation(char *str, int *n1, int *n2, char *op)
{
	char *token = strtok(str, " "); // Returns first token
	//loop that assigns operator and operands
	for(unsigned int i=1; (i<=3) && (token != NULL); i++){
      switch(i) //check if you are parsing the first, second or third token
      {
      	  case 1:
              strcpy(op,token); //operator assignment
              break;

    	   case 2:
              *n1 = atoi(token); //operand assignment
              break;
    	  case 3:
    	      *n2 = atoi(token); //operand assignment
              break;
      }
      token = strtok(NULL, " "); //acquires the next token
   }

   return 0;//number that return if the execution of the function was successful
}

float calculation(int n1, int n2, char op)
{
   //selection of certain operations based on the operator
   switch(op) //check if you are parsing the first, second or third token
   {
       case '+':
          return add(n1, n2); //returns the result of adding n1 to n2
          break;
       case '-':
          return sub(n1, n2); //returns the result of subtracting n1 to n2
          break;
       case '*':
          return mult(n1, n2); //returns the result of the multiplication n1 to n2
          break;
       case '/':
          return division(n1, n2); //returns the result of dividing n1 to n2
          break;
   }
   return 0;
}

float add(int a, int b)
{
    return (float)a + (float)b; //returns the result of adding a to b
}

float sub(int a, int b)
{
    return (float)a - (float)b; //returns the result of subtracting a to b
}

float mult(int a, int b)
{
    return (float)a * (float)b; //returns the result of the multiplication a to b
}

float division(int a, int b)
{
    return (float)a / (float)b; //returns the result of dividing a to b
}

