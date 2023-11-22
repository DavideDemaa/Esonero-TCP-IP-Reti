/*
 * 		check.c
 *      Author: Paolo Ingusci - De Matteis Davide
 */

#include "check.h"

int lenght_check(int leng)
{
	if(leng>30) //check that the maximum length of the string is 30 characters
    {
        puts("The inserted string exceeds the maximum limit (64 characters maximum)");
        return 1; //return 1 if the string is longer than 30 characters
    }
    else
    {
        return 0; //return 0 if the string is shorter than 30 characters
    }
}

int operator_check(char *str)
{
    //check first acquired tocken is an operand (+, x, -, /)
    if((strcmp(str,"+")!=0)&&(strcmp(str,"-")!=0)&&(strcmp(str,"*")!=0)&&(strcmp(str,"/")!=0))
    {
        puts("A correct string operator was not entered, check the format");
        return 1; //returns 1 if the first acquired tocken is an operand (+, x, -, /)
    }
    else
    {
        return 0; //return 0 if the first acquired tocken isn't an operand (+, x, -, /)
    }
}

int num_check(char *str)
{
	if(str[0]!='-' || str[0]!='+' || isdigit(str[0]))
	{
		for(unsigned int i=1; i<strlen(str); i++) //scroll through all characters
		{
			if(!isdigit(str[i]))
		    {
				if(str[i]==' ')
					puts("The operands entered are not of the correct format\nATTENTION -> do not put a space after the last character ");
				else
					puts("The operands entered are not of the correct format");
		        return 1; //return 1 if one or more characters are not digits
		    }
		}
	}

    return 0; //return 1 if all  characters are not digits
}

int string_check(const char *str)
{
    //duplicate of the string so as not to modify it
    char str1[MAX];
    strcpy(str1, str);
    //check the maximum length
	if(strcmp(str1,"=")==0)
	{
		return 0;
	}
	else
	{

		char *token = strtok(str1, " "); // Returns first token
		//cycle in which we will analyze all the tokens of the string
		unsigned int i=1,check_op=0;
		while((i<=3) && (token != NULL)){
			switch(i) //check if you are parsing the first, second or third token
			{
				case 1://check first tocken
					if(operator_check(token))
						return 1;
					token = strtok(NULL, " ");
					break;

				case 2://check second tocken
					if(num_check(token))
						return 1;
					token = strtok(NULL, "\n");
					break;

				case 3://check third tocken
					if(num_check(token))
						return 1;
					check_op=1;
					break;
			 }
			 i++;
		}
		if(check_op==0)
		{
			puts("Fewer than two operands have been entered");
			return 1;
		}
	}
	return 0;
}



