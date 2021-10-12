#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Return true (non-zero) if c is a whitespace character
	('\t or ' ').
	Zero terminators are not printable (therefore false) */
bool delim_character (char c){
	bool is_delim = false;

	//ascii codes for tab and space are 9 and 32 respectively
	if((c == 9) || (c == 32))
	is_delim = true;

	return is_delim;
}

/*Return true (non-zero) if c is a whitespace character
	(not tab or space).
	Zero terminators are not printable (therefore false) */
bool non_delim_character (char c){
	bool is_non_delim = false;

	//ascii codes for whitespace characters
	if((c < 33) || (c > 126)){
		//not tab or space
		if(delim_character(c) == false){
			//zero terminators are false
			if(c != 0){
				is_non_delim = true;
			}
		}
	}

	return is_non_delim;
}

/*Return true if c is not a whitespace character*/
bool non_whitespace_char(char c){
	bool non_whitespace = false;

	if((c>= 33) && (c <= 126)){
		non_whitespace = true;
	}

	return non_whitespace;
}

/*Returns a pointer to the first character of the next
	delimeter-separated word*/
char *word_start (char* str, char c){
	char current = *str;
	int i = 0;

	//check if delim is not a whitespace character
	if(non_whitespace_char(c)){
		while(current == c){
			i += 1;
			current = *(str+i);
			//Check for zero terminator to avoid endless loop
			if(current == 0){
				return (str+i);
			}
		}

		return (str+i);
	}

	//checking for whitespace
	while((delim_character(current) == true)||(non_delim_character(current) == true)){
		i += 1;
		current = *(str+i);
		//Check for zero terminator to avoid endless loop
		if(current == 0){
			return (str+i);
		}
	}

	return (str+i);
}

/*Returns a pointer to the first space character of the zero
	 terminated string*/
char *end_word (char* str, char c){
	char current = *str;
	int i = 0;

	//checking if delim is not a whitespace character
	if(non_whitespace_char(c)){
		while(current != c){
			i += 1;
			current = *(str+i);
			if(current == 0){
				return(str+i);
			}
		}

		return (str+i);
	}

	while((delim_character(current) == false) && (non_delim_character(current) == false)){
		i += 1;
		current = *(str+i);
		//Check for zero terminator to avoid endless loop
		if(current == 0){
			return(str+i);
		}
	}

	return (str+i);
}

//Counts the number of words or tokens
int count_tokens(char* str, char c){
	int count = 0;

	while(*str != '\n'){
		str = word_start(str, c);
		str = end_word(str, c);
		count += 1;
	}

	return count;
}

/*Returns a freshly allocated zero-terminated vector of freshly allocated
space-separated tokens from zero-terminated str.
For example, tokenize("hello world string") would result in:
	tokens[0] = "hello"
	tokens[1] = "world"
	tokens[2] = "string"
	tokens[3] = 0

*/
char* copy_str (char *inStr, short len){
	char* copy = (char*)malloc((len+1)*sizeof(char));
	char current = *inStr;
	int counter = len;

	while(counter > 0){
		*copy = *inStr;
		inStr++;
		copy++;
		counter--;
	}

	return (copy-len);
}

char** tokenize (char* str, char c){
	int numTokens = count_tokens(str, c);
	char** tokens = (char**)malloc((numTokens+1)*sizeof(char*));
	char* tokenStart = word_start(str, c);
	char* tokenEnd = end_word(tokenStart, c);
	int tokenSize = tokenEnd - tokenStart;
	int i = 0;

	//Storing zero-terminated token into vector
	tokens[i] = (char*)malloc((tokenSize+1)*sizeof(char));
	tokens[i] = copy_str(tokenStart, tokenSize);
	tokens[i][tokenSize] = '0';
	i++;
	numTokens--;

	//Store rest of tokens into vector
	while(numTokens > 0){
		tokenStart = word_start(tokenEnd, c);
		tokenEnd = end_word(tokenStart, c);
		tokenSize = tokenEnd - tokenStart;

		tokens[i] = (char*)malloc((tokenSize+1)*sizeof(char));
		tokens[i] = copy_str(tokenStart, tokenSize);
		tokens[i][tokenSize] = '0';
		i++;
		numTokens--;
	}

	//Terminate vector with 0
	tokens[i] = (char*)malloc((1)*sizeof(char));
	tokens[i][0] = '0';
	return tokens;
}

void print_all_tokens(char** tokens){
	int numTokens = 0;
	int i = 0;

	//Count tokens in vector
	while((tokens[i][0] != '0') && (tokens[i][0] != '\0')){
		numTokens++;
		i++;
	}

	for(i = 0; i < numTokens; i++){
		printf("Tokens[%d]: ", i);
		//print token character by character to avoid zero terminator
		for(int j = 0; tokens[i][j] != '0'; j++)
			printf("%c",tokens[i][j]);
		printf("\n");
	}
}
