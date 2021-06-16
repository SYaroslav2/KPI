#pragma once
#include "Parse_Tree.h"
#include "public_defines.h"
bool code_generator(Parse_Tree* tree, const char* str, vector<tokens> lexems);