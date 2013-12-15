#include <stdio.h>
#include <stdlib.h>
#include "my_lib.h"
#include "diff.h"

int main(int argc, char** argv){

	int i = 1;

	OPTIONS op;
	op.arg_no_options = TRUE;	//Default
	op.arg_same = FALSE;			//File are the same (-s & --report-identical-files)
	op.arg_differ = FALSE;			//File are differents (-q & --brief)
	op.arg_help = FALSE;				//Display help message
	
	FILE *file1;
    FILE *file2;
	
	char *f1 = argv[argc-2];
    char *f2 = argv[argc-1];
	
	if (argc < 3 || op.arg_help){
		printf("help ici");
		return 1;
    }
	
	/*
		A Faire
		-i & --ignore-case				//ignore la case
		--ignore-file-name-case		//ignore la case dans LE NOM des fichiers
		--no-ignore-file-name-case	//n'ignore pas la case dans LE NOM des fichiers
		-E --ignore-tab-expension	//ignore les tabulations
		-b --ignore-space-change	//ignore le nombre d'espace
		-w --ignore-all-space			//ignore tous les espaces
		-B --ignore-blank-lines		//ignore les lignes vides

	*/
	
	for(i = 1; i < argc; i++){
		if(!my_strcmp(argv[i], "--normal"))
			op.arg_no_options = TRUE;
			
		if(!my_strcmp(argv[i], "-q") || !my_strcmp(argv[i], "--brief")){
			op.arg_no_options = FALSE;
			op.arg_differ = TRUE;
		}
		
		if(!my_strcmp(argv[i], "-s") || !my_strcmp(argv[i], "--report-identical-files")){
			op.arg_no_options = FALSE;
			op.arg_same = TRUE;
		}
		
		if(!my_strcmp(argv[i], "--help"))
			op.arg_help = TRUE;
		
		//if(!my_strcmp(argv[i], "-a"))
	}
	
	// opening files and test success, report if it doesn't
	if(file1 == NULL || file2 == NULL){
		printf("error: could not open files. \n");
        printf("exiting...");
        return -1;
	}
	
	if(op.arg_same){
		file1 = fopen(f1, "rb");
		file2 = fopen(f2, "rb");
		
		(sameContents(file1,file2))? printf("No diff") : printf("Diff");
		
		fclose(file1);
		fclose(file2);
	}
	
	//Test
	 if(op.arg_no_options){    // cmp files line by line. NO OPTION
		file1 = fopen(f1, "r");
		file2 = fopen(f2, "r");
		
		int count1 = getLines(file1);
		int count2 = getLines(file2);
		
		diff(file1, file2, count1, count2, &op);
	
		printf("resultat de diff ici");
		
		fclose(file1);
		fclose(file2);
	}
	//op.arg_no_options? printf("arg_no_options ENABLED\n") : printf("arg_no_options DISABLED");
	
	return 0;
}