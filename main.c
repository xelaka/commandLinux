#include "my_lib.h"

int main(int argc, char** argv){

	int i = 1;

	OPTIONS op;
	op.arg_no_options = TRUE;	//Default
	op.arg_same = FALSE;			//File are the same
	op.arg_help = FALSE;				//Display help message
	
	for(i = 1; i < argc; i++){
		if(!my_strcmp(argv[i], "--help"))
			op.arg_help = TRUE;
	}
	
	if(op.arg_help){
		help();
		return 1;
	}
	//Test
	//op.arg_no_options? printf("arg_no_options ENABLED\n") : printf("arg_no_options DISABLED");
	
	return 0;
}