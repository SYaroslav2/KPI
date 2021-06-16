#include "CBinTree.h"



int main() {
	//CBinTree Tree;
	CBinTree Tree("Vocabulary.csv");
	printf(" Tree after parse from csv:\n");
	Tree.print_tree();
	printf("\n");
	Tree.print_by_EngWord("Zero");
	printf("\n");
	Tree.print_by_Page(4);
	printf("\n");
	printf(" Deleted by English word test:\n");
	Tree.del_leaf_by_eng("Tabble");
	Tree.print_tree();
	
	return 0;
}
