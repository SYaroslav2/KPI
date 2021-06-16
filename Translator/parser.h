#pragma once
#include "public_defines.h"

bool parser(const char* str, vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems);