#include "my_lib.h"

int main(int argc, char** argv){

	int i = 1;

	OPTIONS op;
	op.arg_no_options = TRUE;	//Default
	op.arg_same = FALSE;			//File are the same (-s & --report-identical-files)
	op.arg_differ = FALSE;			//File are differents (-q & --brief)
	op.arg_help = FALSE;				//Display help message
	
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
	//Test
	//op.arg_no_options? printf("arg_no_options ENABLED\n") : printf("arg_no_options DISABLED");
	
	return 0;
}