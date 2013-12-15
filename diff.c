#include "diff.h"

//count number of lines in the file
int getLines(FILE *f)
{
	char line[MAX_LINES];
	int count=0;
	
	if(ferror(f))
		return -1;
		
	fseek(f, 0, SEEK_SET);
	
	while(fgets(line,MAX_LINES,f) != NULL)
		count++;
		
	return count;
}

//returns BOOLEAN: check if both files have the same contents.
int sameContents(FILE *f1,FILE *f2){
	char c1;
	char c2;
	int same=1;
	int count1=getLines(f1);
	int count2=getLines(f2);
	
	//check size
	if(count1 != count2)
		return 0;
	
	//return cursor to beginning of file
	fseek(f1, 0, SEEK_SET);
	fseek(f2, 0, SEEK_SET);
	
	//check contents
	if(count1 >= count2){
		while(!feof(f1)) {
			c1 = fgetc(f1);
			
			if(ferror(f1))
				return -1;
				
			c2 = fgetc(f2);
			
			if(ferror(f2)) 
				return -1;
				
			if(c1 != c2) {
				same = 0; break;
			}
		}
	}
	else{
		while(!feof(f2)) {
			c2 = fgetc(f2);
			
			if(ferror(f2)) 
				return -1;
				
			c1 = fgetc(f1);
			
			if(ferror(f1))
				return -1;
				
			if(c1 != c2) {
				same = 0; break;
			}
		}
	}
	return same;
}

int getOccurStrArray(char* str, char** array, int size){
	int index = -1;
	int i = 0;
	
	for( i ; i < size ; i++){
		if(my_strcmp(str, array[i]) == 0)
			index = i;
	}
	
	return index;
}

int continueArray(char** array, int size){
	int i = 0;
	int result = 0;
	int number = 0;
	int nextNumber = 0;
	
	for( i = 1 ; i < size-1 ; i++){
		int number = my_atoi(array[i]);
		int nextNumber = my_atoi(array[i+1]);
		if(number != nextNumber-1){
			result = 0;
			return result;
		}
	}
	
	return result;
}

int variousSymbols(char** array, int size){
	int result = 0;
	int i = 0;
	int c = 0;
	int a = 0;
	
	for(i = 1 ; i < size ; i++){
		if(my_strcmp(array[i],"c") == 0)
			c++;
		if(my_strcmp(array[i],"a") == 0)
			a++;
	}
	
	if(a == 0 || c == 0)
		result = 0;
	else
		result = 1;
		
	return result;
}

char** newArray(int size){
	int i = 0;
	
	char** newArray = (char**)malloc(size*sizeof(char*));
	
	for(i = 0 ; i < size ; i++){
		newArray[i] = (char*)malloc(MAX_LINES*sizeof(char));
	}
	
	return newArray;
}

char** convertFileToArray(FILE *f){
	int index = 0;
	int size = getLines(f);
	char line[MAX_LINES];
	char** charArray = (char**)malloc(size*sizeof(char*));
	
	fseek(f, 0, SEEK_SET);
	
	while(fgets(line,MAX_LINES,f) != NULL){
		charArray[index] = (char *)malloc(MAX_LINES*sizeof(char));
		//my_strcpy(charArray[index], line);
		charArray[index] = my_strdup(line);
		index++;
	}
	
	return charArray;
}

char** appendToArray(char* str, char** array, int size){
	
	int i = 0;
	char** newArray = (char**)malloc((size+1)*sizeof(char*));
	
	for( i = 0 ; i < size ; i++){
		newArray[i] = my_strdup(array[i]);
		free(array[i]);
	}
	
	newArray[i] = my_strdup(str);
	free(array);
	
	return newArray;
}

void diff(FILE *f1, FILE *f2, int count1, int count2, OPTIONS *op){
	
	int i = 0;
	int sizeArray = 1;
	int addBetween = 0;
	int changeLines = -1;
	int showFirstAdd = 1;
	
	fseek(f1, 0, SEEK_SET);
	fseek(f2, 0, SEEK_SET);
	
	char** arrayFile1 = convertFileToArray(f1);
	char** arrayFile2 = convertFileToArray(f2);
	
	//Array for final output
	char** lineArrayFile1 = newArray(sizeArray);
	char** lineArrayFile2 = newArray(sizeArray);
	char** operationArray = newArray(sizeArray);
	char** handleFile1 = newArray(sizeArray);
	char** handleFile2 = newArray(sizeArray);
	
	if(count1 == count2){
	
		for( i = 0 ; i < count1 ; i++){
			if(my_strcmp(arrayFile1[i], arrayFile2[i]) != 0){
				char tmp[10];
				sprintf(tmp,"%d", i+1);
				lineArrayFile1 = appendToArray(my_strdup(tmp), lineArrayFile1, sizeArray);
				lineArrayFile2 = appendToArray(my_strdup(tmp), lineArrayFile2, sizeArray);
				operationArray = appendToArray(my_strdup("c"), operationArray, sizeArray);
				handleFile1 = appendToArray(my_strdup(arrayFile1[i]), handleFile1, sizeArray);
				handleFile2 = appendToArray(my_strdup(arrayFile2[i]), handleFile2, sizeArray);
				sizeArray++;
			}
		}
	}
	if(count2 > count1){
		
		for( i = 0 ; i < count2 ; i++){
			if( i < count1){
				if(my_strcmp(arrayFile1[i], arrayFile2[i]) != 0){
					int index = getOccurStrArray(arrayFile1[i], lineArrayFile2, count2);
					if(index != -1){
						int j = 1;
						for(j = 1 ; j <= (index-i) ; j++){
							char tmp[10];
							sprintf(tmp,"%d", i);
							lineArrayFile1 = appendToArray(my_strdup(tmp), lineArrayFile1, sizeArray);
							sprintf(tmp,"%d", j);
							lineArrayFile2 = appendToArray(my_strdup(tmp), lineArrayFile2, sizeArray);
							operationArray = appendToArray(my_strdup("a"), operationArray, sizeArray);
							handleFile1 = appendToArray(my_strdup("NULL"), handleFile1, sizeArray);
							handleFile2 = appendToArray(my_strdup(arrayFile2[j-1]), handleFile2, sizeArray);
							sizeArray++;
						}
					}
					else{
						char tmp[10];
						sprintf(tmp,"%d", i+1);
						lineArrayFile1 = appendToArray(my_strdup(tmp), lineArrayFile1, sizeArray);
						lineArrayFile2 = appendToArray(my_strdup(tmp), lineArrayFile2, sizeArray);
						operationArray = appendToArray(my_strdup("a"), operationArray, sizeArray);
						handleFile1 = appendToArray(my_strdup(arrayFile1[i]), handleFile1, sizeArray);
						handleFile2 = appendToArray(my_strdup(arrayFile2[i]), handleFile2, sizeArray);
						sizeArray++;
					}
				}
				else
					addBetween++;
			}
			else{
				if(changeLines == -1){
					changeLines = i;
					char tmp[10];
					sprintf(tmp, "%d", i);
					lineArrayFile1 = appendToArray(my_strdup(tmp), lineArrayFile1, sizeArray);
					lineArrayFile2 = appendToArray(my_strdup(tmp), lineArrayFile2, sizeArray);
					operationArray = appendToArray(my_strdup("c"), operationArray, sizeArray);
					handleFile1 = appendToArray(my_strdup(arrayFile1[i-1]), handleFile1, sizeArray);
					handleFile2 = appendToArray(my_strdup(arrayFile2[i-1]), handleFile2, sizeArray);
					sizeArray++;
				}
				
				char tmp[10];
				sprintf(tmp, "%d", i+1);
				lineArrayFile1 = appendToArray(my_strdup("NULL"), lineArrayFile1, sizeArray);
				lineArrayFile2 = appendToArray(my_strdup(tmp), lineArrayFile2, sizeArray);
				operationArray = appendToArray(my_strdup("c"), operationArray, sizeArray);
				handleFile1 = appendToArray(my_strdup("NULL"), handleFile1, sizeArray);
				handleFile2 = appendToArray(my_strdup(arrayFile2[i]), handleFile2, sizeArray);
				sizeArray++;
			}
		}
	}
	
	if(sizeArray > 2){
		if(count1 == count2){
			if(continueArray(lineArrayFile1, sizeArray)){
				printf("%s,%s", arrayFile1[1], arrayFile1[sizeArray-1]); // lign file 1
				printf("%s", operationArray[1]); // sign
				printf("%s,%s\n", arrayFile2[1], arrayFile2[sizeArray-1]); // lign file 2
				
				for(i = 1 ; i < sizeArray ; i++) // what to del file1
					printf("< %s\n", handleFile1[i]);
				printf("---\n");
				for(i = 1 ; i < sizeArray ; i++) //what to add file2
					printf("< %s\n", handleFile2[i]);
			}
			else{
				for( i = 1 ; i < sizeArray ; i++){
					printf("%s%s%s\n", lineArrayFile1[i], operationArray[i], lineArrayFile2[i]);
					printf("< %s\n---\n> %s\n", handleFile1[i], handleFile2[i]);
				}
			}
		}
		else if(count2 > count1){ //add or replace
			if(continueArray(lineArrayFile2, sizeArray) && !variousSymbols(operationArray, sizeArray)){ //various
				printf("%s", lineArrayFile1[1]); //file1
				printf("%s", operationArray[1]); // sign
				printf("%s,%s\n", arrayFile2[1], arrayFile2[sizeArray-1]); // lign file 2
				
				for( i = 1 ; i < sizeArray ; i++){
					if(my_strcmp(handleFile1[i], "NULL") != 0)
						printf("< %s\n", handleFile1[i]);
				}
				printf("---\n");
				for( i = 1 ; i < sizeArray ; i++){
					printf("> %s\n", handleFile2[i]);
				}
			}
			else{
				if(addBetween == 1){
					printf("%da%s\n", my_atoi(lineArrayFile1[1])-1, lineArrayFile2[1]);
					printf("> %s\n", handleFile2[1]);
				}
				else{
					int lastValue = 0;
					int value = 0;
					
					for( i = 1 ; i < sizeArray ; i++){
						if(my_strcmp(operationArray[i], "a") == 0){
							if(showFirstAdd){
								value = my_atoi(lineArrayFile2[i]);
								printf("%sa%d", lineArrayFile1[i], value);
								showFirstAdd = 0;
							}
							else
								lastValue = my_atoi(lineArrayFile2[i]);
						}
					}
					if(lastValue > value)
						printf(",%d\n", lastValue);
					else
						printf("\n");
					for( i = 1 ; i < sizeArray ; i++){
						if(my_strcmp(operationArray[i], "a") == 0)
							printf("> %s\n", handleFile2[i]);
					}
					
					showFirstAdd = 1;
					
					for( i = 1 ; i < sizeArray ; i++){
						if(my_strcmp(operationArray[i], "c") == 0){
							if(showFirstAdd){
								printf("%sc", lineArrayFile1[i]);
								showFirstAdd = 0;
							}
							else{
								lastValue = my_atoi(lineArrayFile2[i]);
							}
						}
					}
					
					printf("%d\n", lastValue);
					
					for( i = 1 ; i < sizeArray ; i++){
						if(my_strcmp(operationArray[i], "c") == 0 && my_strcmp(handleFile1[i], "NULL") != 0)
							printf("< %s\n---\n> %s\n %s\n", handleFile1[i], handleFile2[sizeArray-1]);
					}
				}
			}
		}
	}
	else if(count1 == count2){
		printf("%s%s%s\n", lineArrayFile1[1], operationArray[1], lineArrayFile2[1]);
		printf("< %s\n---\n> %s\n", handleFile1[1], handleFile2[1]);
	}
	
	for(i = 0 ; i < sizeArray ; i++){
		free(lineArrayFile1[i]);
		free(lineArrayFile2[i]);
		free(operationArray[i]);
		free(handleFile1[i]);
		free(handleFile2[i]);
	}
	free(lineArrayFile1);
	free(lineArrayFile2);
	free(operationArray);
	free(handleFile1);
	free(handleFile2);
	for(i = 0; i < count1 ; i++)
		free(arrayFile1[i]);
	for(i = 0 ; i < count2 ; i++)
		free(arrayFile2[i]);
	free(arrayFile1);
	free(arrayFile2);
}