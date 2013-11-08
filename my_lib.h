/*
my_lib.h
----------

Projet diff

Rôle : prototypes des fonctions autorisées.
*/

#ifndef MY_LIB_H_INCLUDED
#define MY_LIB_H_INCLUDED

#include <stdio.h>
#include "about.h"

#define TRUE 1
#define FALSE 0

int my_strcmp(char*, char*);
int length(char*);

typedef struct{
	unsigned int arg_no_options;	//Default
	unsigned int arg_same;			//Files are same
	unsigned int arg_differ;			//File are differents
	unsigned int arg_help;			//Display help message
} OPTIONS;	

#endif