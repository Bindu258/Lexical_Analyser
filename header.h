#ifndef HEADER_H
#define HEADER_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef enum
{
    e_success,
    e_failure
}status;

status extention(char *, FILE**,int *);
status parse(FILE *);
status keyword(char *);
status variable(char *);
status identifier(char *);
status operators(char *);
status s_n_literals(char *);
status literals(char *);




#endif
