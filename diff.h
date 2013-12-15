/*
diff.h
----------

Projet diff

Rôle : prototypes de la fonction diff en elle-même
*/

#ifndef DIFF_H_INCLUDED
#define DIFF_H_INCLUDED
#define MAX_LINES	255

#include <stdio.h>
#include <stdlib.h>
#include "my_lib.h"


typedef struct{
	unsigned int arg_no_options;	//Default
	unsigned int arg_same;			//Files are same
	unsigned int arg_differ;			//File are differents
	unsigned int arg_help;			//Display help message
} OPTIONS;

int getLines(FILE *f);
int sameContents(FILE *f1, FILE *f2);
int getOccurStrArray(char* str, char** array, int size);
int continueArray(char** array, int size);
int variousSymbols(char** array, int size);

char** newArray(int size);
char** convertFileToArray(FILE *f);
char** appendToArray(char* str, char** array, int size);

void diff(FILE *f1, FILE *f2, int count1, int count2, OPTIONS *op);

#endif // DIFF_H_INCLUDED
