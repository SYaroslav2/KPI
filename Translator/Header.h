#pragma once
#include "public_defines.h"
vector<data_key> key_words = { {"PROGRAM", 401}, {"BEGIN", 402 }, {"END", 403 }, {"VAR", 404 }, {"LOOP", 405 }, {"ENDLOOP", 406 },  {"INTEGER", 407 }, {"FLOAT", 408 }};
vector<data_key> identificators = { };
vector<data_key> constants = { };
vector<data_key> delimitors_comp = { {":=", 301}, {"..", 302} };
vector<data_key> delimitors = { {"," , 44},{"." , 46}, {":" , 58}, {";" , 59}, {"[" , 91}, {"]" , 93} };

char white_space[] = { char(32), char(9), char(10), char(11), char(12), char(13) };
int const_code = 501;
int ident_code = 1001;
