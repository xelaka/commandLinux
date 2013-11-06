#include "my_lib.h" 

int length(char* value){
	int i = 0;
	while(value[i] != '\0'){
		i++;
	}
	return i;
}

int my_strcmp(char* array1, char* array2){
	
	int value1 = 0;
	int value2 = 0;
	
	int i = 0;
	while(array1[i] != '\0'){
		value1 += (int)array1[i];
		
		i++;
	}
	
	i = 0;
	while(array2[i] != '\0'){
		value2 += (int)array2[i];
		
		i++;
	}
	
	if(value1 > value2)
		return 1;
	if(value1 < value2)
		return -1;
	if(value1 == value2)
		return 0;
}