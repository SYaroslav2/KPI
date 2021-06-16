#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>


using namespace std;
struct Parse_Tree_Node {
	char name[25];
	int lex_code;
	Parse_Tree_Node* ancestor;
	vector<Parse_Tree_Node*> descendants;
};

class Parse_Tree
{
public:

	Parse_Tree_Node* root = NULL;
	Parse_Tree_Node* current_node;

	Parse_Tree();
	~Parse_Tree();
	void add(char name[], int lex_code);
	bool level_up();
	void _print(Parse_Tree_Node* root, int level, FILE* file1);
	void print(FILE* file1);
};

