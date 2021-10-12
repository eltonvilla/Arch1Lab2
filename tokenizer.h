bool delim_character (char c);
bool non_delim_character (char c);
bool non_whitespace_character (char c);
char *word_start (char* str, char c);
char *end_word (char* str, char c);
int count_tokens (char* str, char c);
char *copy_str (char *inStr, short len);
char** tokenize (char* str, char c);
void print_all_tokens(char** tokens);
