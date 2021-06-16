#include "CBinTree.h"



CBinTree::CBinTree() {
	
	root = NULL;
}



CBinTree::CBinTree(const char* csv) {

	root = NULL;
	char* string, * str_ptr;
	int i, flag, j, count, lenght, counter;
	char str[256], str_1[256];
	FILE* csv_File;
	Vocabulary temp;
	csv_File = fopen(csv, "r");
	if (!csv_File) return;

	Leaf* Elem;
	flag = 0;
	count = 0;
	i = 0;
	while (fgets(str, 255, csv_File)) {
		fseek(csv_File, 0, SEEK_SET);
		counter = 0;
		while (fgets(str_1, 255, csv_File) && counter < i) {
			counter++;
			flag = 0;
			if (strcmp(str, str_1) == 0)
				flag = 1;
		}

		if (flag == 1)
		{
			i++;
			count++;
			continue;
		}
		
		lenght = strlen(str);
		string = (char*)malloc(lenght + 1);
		str_ptr = string;
		counter = 0;
		for (j = 0; j < lenght; j++) {
			if (str[j] == ';') {
				string[j] = '\0';
				counter++;
			}
			else
				string[j] = str[j];
		}
		string[j] = '\0';
		strcpy(temp.m_EngWord, str_ptr);
		str_ptr += strlen(str_ptr) + 1;
		strcpy(temp.m_ItaWord, str_ptr);
		str_ptr += strlen(str_ptr) + 1;
		count = atoi(str_ptr);
		temp.m_Page = count;
		free(string);
		Elem = new Leaf;
		Elem->INFO = temp;
		add_leaf(Elem, root);
		i++;
	}
	fclose(csv_File);
	
}



CBinTree::~CBinTree() {
	
	del_all(root);
}



void CBinTree::add_leaf(Leaf* leaf, Leaf*& root) {
	
	if (!root) {
		root = new Leaf;
		root->INFO = leaf->INFO;
		root->left = NULL;
		root->right = NULL;
	}
	else {
		if (strcmp(leaf->INFO.m_EngWord, root->INFO.m_EngWord) > 0)
			add_leaf(leaf, root->right);
		else
			add_leaf(leaf, root->left);
	}

}



void CBinTree::print_subtree(Leaf* root) {
	
	if (root) {
		print_subtree(root->left);
		root->INFO.print();
		print_subtree(root->right);
	}

}



void CBinTree::print_tree() {
	
	if (!root)
		printf("\n Tree is empty\n");
	else
		print_subtree(root);

}



void CBinTree::del_all(Leaf* root) {
	
	if (root) {
		del_all(root->left);
		del_all(root->right);
		delete root;
		root = NULL;
	}

}



int CBinTree::Find_Word(Leaf* root, const char* str) {
	
	if (root) {
		printf(" %s", root->INFO.m_EngWord);
		Find_Word(root->left, str);
		if (strcmp(root->INFO.m_EngWord, str) == 0)
			return 1;
		Find_Word(root->right, str);
	}

}



int CBinTree::Find_Page(Leaf* root, int integer) {

	if (root) {

		Find_Page(root->left, integer);
		if (root->INFO.m_Page == integer)
			return 1;
		Find_Page(root->right, integer);
	}

}



void CBinTree::print_by_EngWord(const char* EngWord) {
	
	int res = Find_Word(root, EngWord);


	if (Find_Word(root, EngWord) != 1)
	{
		abort();
	}

	printf("\n Looking for %s's italian equivalent:\n", EngWord);
	print_By_EngWord(root, EngWord);

}



void CBinTree::print_By_EngWord(Leaf* pointer, const char* EngWord) {

	
	if (pointer == NULL) return;
	if (strcmp(pointer->INFO.m_EngWord, EngWord) == 0) pointer->INFO.print();

	print_By_EngWord(pointer->left, EngWord);
	print_By_EngWord(pointer->right, EngWord);

}



void CBinTree::print_by_Page(int Page) {

	if (Find_Page(root, Page) != 1)
	{
		abort();
	}
	printf("\n Looking for all word from %d page:\n", Page);
	print_By_Page(root, Page);

}



void CBinTree::print_By_Page(Leaf* pointer, int Page) {

	if (pointer == NULL) return;
	if (pointer->INFO.m_Page == Page) pointer->INFO.print();

	print_By_Page(pointer->left, Page);
	print_By_Page(pointer->right, Page);
	
}



void CBinTree::del_leaf_by_eng(const char* EngWord) {

	if (Find_Word(root, EngWord) != 1)
	{
		abort();
	}
	Leaf* tmp = this->root;
	Leaf* tmp_1 = NULL;
	if (!tmp) return;
	while (strcmp(tmp->INFO.m_EngWord, EngWord) != 0) {
		tmp_1 = tmp;
		if (strcmp(tmp->INFO.m_EngWord, EngWord) < 0)
			tmp = tmp->right;
		else
			tmp = tmp->left;
		
		if (tmp == NULL)
			return;
	}

	Leaf* Deleted = NULL;
	if ((tmp->left == NULL) || (tmp->right == NULL)) {
		Leaf* temp = NULL;
		Deleted = tmp;
		if (tmp->right)
			temp = tmp->right;
		else if (tmp->left)
			temp = tmp->left;
		if (!tmp_1)
			root = temp;
		else {
			if (tmp_1->right == tmp)
				tmp_1->right = temp;
			else
				tmp_1->left = temp;
		}
	}
	else {
		Leaf* tmp_2 = tmp->left;
		Leaf* tmp_3 = tmp;
		while (tmp_2->right) {
			tmp_3 = tmp_2;
			tmp_2 = tmp_2->right;
		}
		tmp->INFO = tmp_2->INFO;
		Deleted = tmp_2;
		if (tmp_3->right == tmp_2)
			tmp_3->right = NULL;
		else
			tmp_3->left = NULL;
	}
	delete Deleted;

}