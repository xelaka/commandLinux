#include "my_lib.h"

int main(int argc, char** argv){

	int i = 1;

	OPTIONS op;
	op.arg_no_options = TRUE;	//Default
	op.arg_same = FALSE;			//File are the same (-s & --report-identical-files)
	op.arg_differ = FALSE;			//File are differents (-q & --brief)
	op.arg_help = FALSE;				//Display help message
	
	FILE *f1;
    FILE *f2;
	
	char *fic1 = argv[argc-2];
    char *fic2 = argv[argc-1];
	
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
	
	if(op.arg_help){
		help();
		return 1;
	}
	
	// opening files and test success, report if it doesn't
	f1 = fopen(fic1, "r");
    f2 = fopen(fic2, "r");
		
	if(f1 == NULL || f2 == NULL){
		printf("error: could not open files. \n");
		printf("exiting...");
		return -1;
	}
	
	//Test
	if(op.arg_no_options){    // cmp files line by line. NO OPTION
		printf("arg_no_option NO options\n");
		diff(f1, f2, &op);
	}
	//op.arg_no_options? printf("arg_no_options ENABLED\n") : printf("arg_no_options DISABLED");
	
	return 0;
}