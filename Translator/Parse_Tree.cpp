#define _CRT_SECURE_NO_WARNINGS
#include "Parse_Tree.h"


Parse_Tree::Parse_Tree() {
	root = NULL;
	current_node = NULL;
}


Parse_Tree::~Parse_Tree() {

}


void Parse_Tree::add(char name[], int lex_code) {
    Parse_Tree_Node* new_node = new Parse_Tree_Node;
    strcpy(new_node->name, name);
    new_node->lex_code = lex_code;
    if (this->root == NULL) {
        this->current_node = new_node;
        this->root = new_node;
    } 
    else {
        Parse_Tree_Node* ancestor_node = this->current_node;
        new_node->ancestor = ancestor_node;
        this->current_node->descendants.push_back(new_node);
        this->current_node = new_node;
    }
}


bool Parse_Tree::level_up() {
    if (this->current_node->ancestor != NULL) {
        this->current_node = this->current_node->ancestor;
        return true;
    }
    return false;
}


void Parse_Tree::_print(Parse_Tree_Node* root, int level, FILE* file1) {
    if (root == NULL) {
        return;
    }
    char buf[128] = "";
    char buf_for_[64];
    int desc_lvl;
    for (int i = 0; i < level; i++) {
        strcat(buf, "--");
    }
    if (root->lex_code == 0)
        sprintf(buf, "%s%s \n", buf, root->name);
    else 
        sprintf(buf, "%s%d %s \n", buf, root->lex_code, root->name);
    fprintf(file1, "%s \n", buf);
    if (root->descendants.size() != 0) {
        for (int i = 0; i < root->descendants.size(); i++) {
            desc_lvl = level;
            _print(root->descendants[i], ++desc_lvl, file1);
        }
    }
}


void Parse_Tree::print(FILE* file1) {
    
    this->_print(this->root, 0, file1);
    fclose(file1);
}