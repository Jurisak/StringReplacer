#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "errno.h"
#include "string.h"


typedef enum{ERROR=-2, END=-1} error_returns;


int get_and_check_char(char *c){
	*c = getchar();
	if (!(isalpha(*c) || isspace(*c)))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

int is_end_of_sequence(char c){
	return c == '0';
}

int check_char(char c){
	if (!(isalpha(c)))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}


int get_size_of_pattern_sequence(char *pattern, int i, char *c){
	int size = 1;
	if(*c == '0')
		return 0;
	while(*c != '0'){
		for(int index=0; index < i; index++){
			if(pattern[index] == *c){
				*c = getchar();
				if(check_char(*c) && !is_end_of_sequence(*c)){
					return ERROR;
				}
			}
			else{
				return size;
			}
		}
		++size;
	}
	return size;
}

void print_pattern(char* pattern, int i){
	for(int index = 0; index < i; index++){
		printf("%c", pattern[index]);
	}
}

int is_char_in_pattern(char *pattern, int i, char c){
	for(int index=0; index < i;index++){
		if(pattern[index] == c)
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int adjust_size(int size){
	if(size > 9)
		return 0;
	return size;
}


int main()
{
	char c;
	int i = 0;
	int max = 9;
	int size = 0;
	char *pattern = (char *)malloc(10*sizeof(char));
	
	c = getchar();
	pattern[i] = c;
	++i;
	while(1){
		c = getchar();
		if(is_end_of_sequence(c))
			break;
		if(check_char(c)){
			fprintf(stderr, "ERROR: Wrong input. Contains non alphabetic characters\n");
			free(pattern);
			exit(EXIT_FAILURE);
		}
		if((i == 0) || (!is_char_in_pattern(pattern, i, c))){
			pattern[i] = c;
			++i;
			if (i == max){
				pattern = (char*)realloc(pattern, (10+max)*sizeof(char));
				max += 10;
			}
		}
		else{
			size = get_size_of_pattern_sequence(pattern, i, &c);
			if(size == ERROR){
				fprintf(stderr, "ERROR: Wrong input. Contains non alphabetic characters\n");
				free(pattern);
				exit(EXIT_FAILURE);
			}
			printf("%d", adjust_size(size));
			print_pattern(pattern, i);
			if(is_end_of_sequence(c))
				break;
			pattern[0]= c;
			i = 1;	
		}
	}
	size = get_size_of_pattern_sequence(pattern, i, &c);
	printf("1");
	print_pattern(pattern, i);
	free(pattern);
	return 0;
}