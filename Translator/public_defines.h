#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>


using namespace std;


struct data_key {
	char name[8];
	int key;
};


struct tokens {
	char name[25];
	int lex_code;
	int row_id;
	int col_id;
};
