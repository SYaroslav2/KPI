#pragma once

int in_const_table(char str[]);
int in_ident_table(char str[]);
int in_key_words_table(char str[]);
int in_delimiter(char ch);
bool is_letter(char ch);
bool is_digit(char ch);
bool is_delimiter(char ch);
bool is_whitespace(char ch);
bool lexer(const char* str);


