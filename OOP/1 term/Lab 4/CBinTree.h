#pragma once

#include "Vocabulary.h"



class CBinTree
{

	struct Leaf {
		Leaf* left = NULL, * right = NULL;
		Vocabulary INFO;
	};

	Leaf* root;

	void print_By_EngWord(Leaf* pointer, const char* EngWord);
	void print_By_Page(Leaf* pointer, int Page);
	void del_all(Leaf* root);
	void print_subtree(Leaf* root);
	void add_leaf(Leaf* leaf, Leaf*& root);
	
	int Find_Page(Leaf* root, int integer);
	

public:
	
	CBinTree();
	CBinTree(const char* csv);
	~CBinTree();

	int Find_Word(Leaf* root, const char* str);
	void print_by_EngWord(const char* EngWord);
	void del_leaf_by_eng(const char* EngWord);
	void print_tree();
	void print_by_Page(int);

};