/*
my_lib.h
----------

Projet diff

Rôle : prototypes des fonctions autorisées.
*/

#ifndef MY_LIB_H_INCLUDED
#define MY_LIB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

char* my_strdup(const char* s1);
char* my_strcpy(char* dest, const char* src);

int length(char* input);
int my_strcmp(char* array1, char* array2);	
int my_atoi(char* value);

#endif