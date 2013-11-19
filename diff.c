#include "diff.h"

void diff(FILE *f1, FILE *f2, OPTIONS *op){

	int currLines1 = 0;
	int currLines2 = 0;

	int numberLine1 = 0;
    int numberLine2 = 0;
    int offset1 = -1;
    int offset2 = -1;
	
	char line_f1[MAX_LINE_LENGTH];
    char line_f2[MAX_LINE_LENGTH];
    char line_f1_tmp[MAX_LINE_LENGTH];
    char line_f2_tmp[MAX_LINE_LENGTH];
    char* f1p_tmp = NULL;
    char* f2p_tmp = NULL;
	
	while(fgets(line_f1, MAX_LINE_LENGTH, f1) && fgets(line_f2, MAX_LINE_LENGTH, f2)){
	
		currLines1++;
		currLines2++;
		
		line_f1[length(line_f1)-1] = '\0';
		line_f2[length(line_f2)-1] = '\0';
		
		/*
		printf("\t %d<%s> \n", currLines1, line_f1);
		printf("\t %d<%s> \n", currLines2, line_f2);
		*/
		
		if(my_strcmp(line_f1, line_f2) != 0){
			// Read file2 for equal lines
			numberLine2 = 0;
			offset2 = ftell(f2);       // save current file position
			FILE* f2tmp = fdopen(dup(fileno(f2)), "r");     // duplicate file pointer
			fseek(f2tmp, offset2, SEEK_SET);     // set temp file pointer to current position

			f2p_tmp = fgets(line_f2_tmp, MAX_LINE_LENGTH, f2tmp);
			line_f2_tmp[length(line_f2_tmp)-1] = '\0';
				while((f2p_tmp != NULL) && ((my_strcmp(line_f1, line_f2_tmp) != 0)) ){
					// Skip if lines are different
					numberLine2++;
					f2p_tmp = fgets(line_f2_tmp, MAX_LINE_LENGTH, f2tmp);
					line_f2_tmp[length(line_f2_tmp)-1] = '\0';
				}
			fclose(f2tmp);
			
			 // Read file1 for equal lines
            numberLine1 = 0;
            offset1 = ftell(f1);       // save current file position
            FILE* f1tmp = fdopen(dup(fileno(f1)), "r");     // duplicate file pointer
            fseek(f1tmp, offset1, SEEK_SET);       // set temp file pointer to current position

            f1p_tmp = fgets(line_f1_tmp, MAX_LINE_LENGTH, f1tmp);
            line_f1_tmp[length(line_f1_tmp)-1] = '\0';
            while((f1p_tmp != NULL) && ((my_strcmp(line_f2, line_f1_tmp) != 0))){
                // Skip different lines
                numberLine1++;
                f1p_tmp = fgets(line_f1_tmp, MAX_LINE_LENGTH, f1tmp);
                line_f1_tmp[length(line_f1_tmp)-1] = '\0';
            }
            fclose(f1tmp);
			
			//test
			//printf("numberLine1: %d \n", numberLine1);
            //printf("numberLine2: %d \n\n", numberLine2);
			
			// Compare read lines (find minimum)
            if ((f1p_tmp != NULL) || (f2p_tmp != NULL)){
                if (numberLine2 < numberLine1){
                    // Scan through second file looking for equal lines
                    printf("+[f2, %d]: %s \n", currLines2, line_f2);

                    offset2 = ftell(f2);
                    FILE* f2t = fdopen (dup (fileno (f2)), "r");
                    fseek(f2t, offset2, SEEK_SET);
                    int i=0;
                    for(i=0; i<numberLine2; i++){
                        // added
                        fgets(line_f2_tmp, MAX_LINE_LENGTH, f2t);
                        line_f2_tmp[length(line_f2_tmp)-1] = '\0';
                        printf("+[f2, %d]: %s \n", currLines2+i+1, line_f2_tmp);
                    }
                    fgets(line_f2_tmp, MAX_LINE_LENGTH, f2t);
                    line_f2_tmp[length(line_f2_tmp)-1] = '\0';
                    offset2 = ftell(f2t);
                    fseek(f2, offset2, SEEK_SET);
                    fclose(f2t);
                    currLines2 += numberLine2+1;


                }else{
                    // Read file1 for equal lines
                    printf("-[f1, %d]: %s \n", currLines1, line_f1);

                    offset1 = ftell(f1);
                    FILE* f1t = fdopen (dup (fileno (f1)), "r");
                    fseek(f1t, offset1, SEEK_SET);

                    int i=0;
                    for(i=0; i<numberLine1; i++){
                        //delete
                        fgets(line_f1_tmp, MAX_LINE_LENGTH, f1t);
                        line_f1_tmp[length(line_f1_tmp)-1] = '\0';
                        printf("-[f1, %d]: %s \n", currLines1+i+1, line_f1_tmp);
                    }

                    fgets(line_f1_tmp, MAX_LINE_LENGTH, f1t);
                    line_f1_tmp[length(line_f1_tmp)-1] = '\0';
                    offset1 = ftell(f1t);
                    fseek(f1, offset1, SEEK_SET);
                    fclose(f1t);
                    currLines1 += numberLine1+1;
                }

            }
			else{
                // change
                printf("![f1, %d]: %s \n", currLines1, line_f1);
                printf("![f2, %d]: %s \n", currLines2, line_f2);
            }
		}
	}
	
	 while(fgets(line_f2, MAX_LINE_LENGTH, f2)){
        line_f2[length(line_f2)-1] = '\0';
        currLines2++;
        printf("+[f2, %d]: %s \n", currLines2, line_f2);
    }

    while(fgets(line_f1, MAX_LINE_LENGTH, f1)){
        line_f1[length(line_f1)-1] = '\0';
        currLines1++;
        printf("+[f1, %d]: %s \n", currLines1, line_f1);
    }
	
	printf("\n\nSuccess: Files compared successfully !\n\n");
	
}