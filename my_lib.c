#include "my_lib.h" 

char* my_strdup(const char* s1){
	
	char* copy;
	int tmp = 0;
	int i = 0;
	
	tmp = length((char *)s1);
	
	copy=malloc(sizeof(char)*tmp);
	
	while(s1[i] != '\0'){
		copy[i] = s1[i];
		i++;
	}
	
	copy[i]='\0';
	
	return copy;
}

char* my_strcpy(char* dst, const char* src){

	char* ptr = dst;
	
	while ( *dst++ = *src++ );
		
	return ptr;
}

int length(char* value){
	int i = 0;
	
	if(value == NULL)
		return 0;
		
	while(value[i] != '\0' && value[i] != '\n'){
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

int my_atoi(char* value){
	int result=0;
	int current=0;
	int i=0;
	int sign=1;
	
	if(value[i] == '-'){
		sign = (-1);
		i++;
	}
	
	while(value[i] != '\0'){
		if(value[i] == 46){
			result *= sign;
			return result;
		}
		
		current=value[i];
		
		if(current < 48 || current > 57){
			return 0;
		}
		
		result = result*10 + value[i] - 48;
		i++;
	}
	result *= sign;
	return result;
}