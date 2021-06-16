#define _CRT_SECURE_NO_WARNINGS
#include "parser.h"
#include "Parse_Tree.h"
#include "code_generator.h"

FILE* file1;
Parse_Tree* parser_tree;
char temp[128];

int key_2;
int loop_counter = 0;
bool pars_res = true;

bool is_variable(vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count);


bool is_proc_identifier(vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count) {
	for (int i = 0; i < identificators.size(); i++) {
		if (lexems[count].lex_code == identificators[i].key) {
			strcpy(temp, "<procedure-identifier>");
			parser_tree->add(temp, 0);
			strcpy(temp, "<identifier>");
			parser_tree->add(temp, 0);
			parser_tree->add(identificators[i].name, identificators[i].key);
			count++;
			return true;
		}
			
	}
	return false;
}


bool is_constant(vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count) {
	for (int i = 0; i < constants.size(); i++) {
		if (lexems[count].lex_code == constants[i].key) {
			strcpy(temp, "<unsigned-integer>");
			parser_tree->add(temp, 0);
			parser_tree->add(lexems[count].name, lexems[count].lex_code);
			count++;
			return true;
		}
	}
	return false;
}



bool is_dimension(vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count) {
	if (lexems[count].lex_code == 91) {
		count++;
		strcpy(temp, "[<expression>]");
		parser_tree->add(temp, 0);
		if (is_constant(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
			if (lexems[count].lex_code == 93) {
				count++;
				return true;
			}
			sprintf(temp, "Parser: Error (line %d, column %d): ']' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
			fprintf(file1, "%s \n", temp);
			pars_res = false;
			return false;
		}
		if (is_variable(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
			if (lexems[count].lex_code == 93) {
				count++;
				return true;
			}
			sprintf(temp, "Parser: Error (line %d, column %d): ']' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
			fprintf(file1, "%s \n", temp);
			pars_res = false; 
			return false;
		}
		else { 
			sprintf(temp, "Parser: Error (line %d, column %d): '<expression>' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
			fprintf(file1, "%s \n", temp);
			pars_res = false; 
			return false;
		}
	}
	strcpy(temp, "<empty>");
	parser_tree->add(temp, 0);
}


bool is_identifier(vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count) {
	for (int i = 0; i < identificators.size(); i++) {
		if (lexems[count].lex_code == identificators[i].key) {
			strcpy(temp, "<variable>");
			parser_tree->add(temp, 0);
			strcpy(temp, "<variable-identifier>");
			parser_tree->add(temp, 0);
			parser_tree->level_up();
			strcpy(temp, "<dimension>");
			parser_tree->add(temp, 0);
			parser_tree->level_up();
			parser_tree->current_node = parser_tree->current_node->descendants[0];
			strcpy(temp, "<identifier>");
			parser_tree->add(temp, 0);
			parser_tree->add(lexems[count].name, lexems[count].lex_code); 
			while (strcmp(parser_tree->current_node->name, "<variable>") != 0) {
				parser_tree->level_up();
			}
			parser_tree->current_node = parser_tree->current_node->descendants[1];
			count++;
			if (is_dimension(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
				if (pars_res == false)
					return false;
			}

			return true;
		}

	}
	return false;
}


bool is_variable(vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count) {
	if (!is_identifier(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
		return false;
	}
	if (lexems[count].lex_code == 91) {
		count++;
		if (is_constant(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
			if (lexems[count].lex_code == 93) {
				count++;
				return true;
			}
			return false;
		}
		if (is_variable(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
			return true;
		}
		else return false;
	}
	return true;
}



bool is_var_identifier(vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count) {
	for (int i = 0; i < identificators.size(); i++) {
		if (lexems[count].lex_code == identificators[i].key) {
			strcpy(temp, "<declaration>");
			parser_tree->add(temp, 0);
			parser_tree->level_up();
			strcpy(temp, "<declarations-list>");
			parser_tree->add(temp, 0);
			parser_tree->level_up();
			parser_tree->current_node = parser_tree->current_node->descendants[0];
			strcpy(temp, "<variable-identifier>");
			parser_tree->add(temp, 0);
			strcpy(temp, "<identifier>");
			parser_tree->add(temp, 0);
			parser_tree->add(identificators[i].name, identificators[i].key);
			count++;
			return true;
		}

	}
	return false;
}


bool is_massive(int key, vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count) {
	if (lexems[count].lex_code == 91) {
		strcpy(temp, "<attribute>");
		parser_tree->add(temp, 0);
		parser_tree->level_up();
		strcpy(temp, "<attributes-list>");
		parser_tree->add(temp, 0);
		parser_tree->level_up();
		parser_tree->current_node = parser_tree->current_node->descendants[key];
		strcpy(temp, "[<range>]");
		parser_tree->add(temp, 0);
		count++;
		if (is_constant(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
			while (strcmp(parser_tree->current_node->name, "[<range>]") != 0) {
				parser_tree->level_up();
			}
			if (lexems[count].lex_code == 302) {
				parser_tree->add(lexems[count].name, lexems[count].lex_code);
				parser_tree->level_up();
				count++;
				if (is_constant(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
					if (lexems[count].lex_code == 93) {
						while ((strcmp(parser_tree->current_node->name, "<attributes-list>") != 0) && (strcmp(parser_tree->current_node->name, "<declaration>") != 0)) {
							parser_tree->level_up();
						}
						if (strcmp(parser_tree->current_node->name, "<declaration>") == 0) {
							parser_tree->current_node = parser_tree->current_node->descendants[3];
						}
						else
							parser_tree->current_node = parser_tree->current_node->descendants[1];
						count++;
						return true;
					}
					sprintf(temp, "Parser: Error (line %d, column %d): ']' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
					fprintf(file1, "%s \n", temp);
					pars_res = false;
					return false;
				}
				sprintf(temp, "Parser: Error (line %d, column %d): '<unsigned-integer>' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
				fprintf(file1, "%s \n", temp);
				pars_res = false;
				return false;
			}
			sprintf(temp, "Parser: Error (line %d, column %d): '..' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
			fprintf(file1, "%s \n", temp);
			pars_res = false;
			return false;
		}
		sprintf(temp, "Parser: Error (line %d, column %d): '<unsigned-integer>' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
		fprintf(file1, "%s \n", temp);
		pars_res = false;
		return false;
	}
	return false;
}


bool is_attribute_list(vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count) {
	
	if (lexems[count].lex_code == 407 || lexems[count].lex_code == 408) {
		strcpy(temp, "<attribute>");
		parser_tree->add(temp, 0);
		parser_tree->level_up();
		strcpy(temp, "<attributes-list>");
		parser_tree->add(temp, 0);
		parser_tree->level_up();
		parser_tree->current_node = parser_tree->current_node->descendants[0];
		parser_tree->add(lexems[count].name, lexems[count].lex_code);
		while (strcmp(parser_tree->current_node->name, "<attributes-list>") != 0) {
			parser_tree->level_up();
		}
		parser_tree->current_node = parser_tree->current_node->descendants[1];
		count++;
		return true;
	}
	int counter = 0;
	while (is_massive(0, key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
		counter++;
	}
	if (pars_res == false)
		return false;

	if (counter != 0)
		return true;
	return false;

}



bool is_attribute(vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count) {
	if (lexems[count].lex_code == 407 || lexems[count].lex_code == 408) {
		strcpy(temp, "<attribute>");
		parser_tree->add(temp, 0);
		parser_tree->level_up();
		strcpy(temp, "<attributes-list>");
		parser_tree->add(temp, 0);
		parser_tree->level_up();
		parser_tree->current_node = parser_tree->current_node->descendants[2];
		parser_tree->add(lexems[count].name, lexems[count].lex_code);
		while (strcmp(parser_tree->current_node->name, "<declaration>") != 0) {
			parser_tree->level_up();
		}
		parser_tree->current_node = parser_tree->current_node->descendants[3];
		count++;
		while (is_attribute_list(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {

		}
		if (pars_res == false)
			return false;
		strcpy(temp, "<empty>");
		parser_tree->add(temp, 0);

		return true;
	}
	else {
		int counter = 0;
		while (is_massive(2, key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
			counter++;
		}
		if (pars_res == false)
			return false;

		if (counter != 0) {
			while (strcmp(parser_tree->current_node->name, "<declaration>") != 0) {
				parser_tree->level_up();
			}
			parser_tree->current_node = parser_tree->current_node->descendants[3];
			while (is_attribute_list(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
				if (pars_res == false)
					return false;
			}
			if (strcmp(parser_tree->current_node->name, "<empty>") != 0) {
				strcpy(temp, "<empty>");
				parser_tree->add(temp, 0);
			}
			return true;
		}
		strcpy(temp, "<empty>");
		parser_tree->add(temp, 0);
		return false;
	}
	return false;

}


bool is_declaration(vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count) {
	if (is_var_identifier(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
		if (lexems[count].lex_code == 58) {
			while (strcmp(parser_tree->current_node->name, "<declaration>") != 0) {
				parser_tree->level_up();
			}
			parser_tree->add(lexems[count].name, lexems[count].lex_code);
			count++;
			int counter = 0;
			parser_tree->level_up();
			if(is_attribute(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
				counter++;
			}
			if (pars_res == false)
				return false;
			if (counter == 0){
				sprintf(temp, "Parser: Error (line %d, column %d): '<attribute>' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
				fprintf(file1, "%s \n", temp);
				pars_res = false;
				return false;
			}
			if (lexems[count].lex_code == 59) {
				while (strcmp(parser_tree->current_node->name, "<declaration>") != 0) {
					parser_tree->level_up();
				}
				parser_tree->add(lexems[count].name, lexems[count].lex_code);
				parser_tree->level_up();
				parser_tree->current_node = parser_tree->current_node->ancestor->descendants[1];
				count++;
				return true;
			}
			else {
				sprintf(temp, "Parser: Error (line %d, column %d): ';' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
				fprintf(file1, "%s \n", temp);
				pars_res = false;
				return false;
			}
		}
		sprintf(temp, "Parser: Error (line %d, column %d): ':' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
		fprintf(file1, "%s \n", temp);
		pars_res = false;
		return false;
	}
	return false;
}


bool is_statement(int key, vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems, int& count) {

	if (lexems[count].lex_code == 405) {
		loop_counter++;
		if(key_2 == 0){
			strcpy(temp, "<statement>");
			parser_tree->add(temp, 0);
			parser_tree->level_up();
			strcpy(temp, "<statements-list>");
			parser_tree->add(temp, 0);
			parser_tree->level_up();
			parser_tree->current_node = parser_tree->current_node->descendants[0];
		}
		parser_tree->add(lexems[count].name, lexems[count].lex_code);
		parser_tree->level_up();
		strcpy(temp, "<statements-list>");
		parser_tree->add(temp, 0);
		strcpy(temp, "<statement>");
		parser_tree->add(temp, 0);
		parser_tree->level_up();
		strcpy(temp, "<statements-list>");
		parser_tree->add(temp, 0);
		parser_tree->level_up();
		parser_tree->current_node = parser_tree->current_node->descendants[0];
		count++;
		key_2 = 1;
		while (is_statement(1, key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
			
			while (strcmp(parser_tree->current_node->name, "<statements-list>") != 0) {
				parser_tree->level_up();
			}
			if(parser_tree->current_node->descendants.size() != 0)
				parser_tree->current_node = parser_tree->current_node->descendants[1];
			if (lexems[count].lex_code == 406) {
				parser_tree->current_node;
				break;
			}
			strcpy(temp, "<statement>");
			parser_tree->add(temp, 0);
			parser_tree->level_up();
			strcpy(temp, "<statements-list>");
			parser_tree->add(temp, 0);
			parser_tree->level_up();
			parser_tree->current_node = parser_tree->current_node->descendants[0];
		}
		if(lexems[count].lex_code == 406){
			strcpy(temp, "<empty>");
			parser_tree->add(temp, 0);
			parser_tree->level_up();
			while (strcmp(parser_tree->current_node->descendants[0]->name, "LOOP") != 0) {
				parser_tree->level_up();
			}
			parser_tree->add(lexems[count].name, lexems[count].lex_code);
			parser_tree->level_up();
			count++;
			if (lexems[count].lex_code != 59) {
				sprintf(temp, "Parser: Error (line %d, column %d): ';' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
				fprintf(file1, "%s \n", temp);
				pars_res = false;
				return false;
			}
			else {
				parser_tree->add(lexems[count].name, lexems[count].lex_code);
				parser_tree->level_up();
				parser_tree->level_up();
				parser_tree->current_node = parser_tree->current_node->descendants[1];
				if (lexems[count+1].lex_code != 403 && lexems[count+1].lex_code != 406 && key_2 == 0) {
					strcpy(temp, "<statement>");
					parser_tree->add(temp, 0);
					parser_tree->level_up();
					strcpy(temp, "<statements-list>");
					parser_tree->add(temp, 0);
					parser_tree->level_up();
					parser_tree->current_node = parser_tree->current_node->descendants[0];
				}
				loop_counter--;
				if(loop_counter == 1){
					key_2 = 0;
				}
				count++;
				return true;
			}
		}
		sprintf(temp, "Parser: Error (line %d, column %d): 'ENDLOOP' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
		fprintf(file1, "%s \n", temp);
		pars_res = false;
		return false;
	}
	

	if (is_variable(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
		if (lexems[count].lex_code == 301) {
			while (strcmp(parser_tree->current_node->name, "<statement>") != 0) {
				parser_tree->level_up();
			}
			parser_tree->add(lexems[count].name, lexems[count].lex_code);
			count++;
			parser_tree->level_up();
			strcpy(temp, "<expression>");
			parser_tree->add(temp, 0);
			if (is_constant(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
				if (lexems[count].lex_code == 59) {
					while (strcmp(parser_tree->current_node->name, "<statement>") != 0) {
						parser_tree->level_up();
					}
					parser_tree->add(lexems[count].name, lexems[count].lex_code);
					parser_tree->level_up();
					if (key == 0) {
						while (strcmp(parser_tree->current_node->name, "<statements-list>") != 0) {
							parser_tree->level_up();
						}
						parser_tree->current_node = parser_tree->current_node->descendants[1];
					}
					count++;
					return true;
				}
				else {
					sprintf(temp, "Parser: Error (line %d, column %d): ';' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
					fprintf(file1, "%s \n", temp);
					pars_res = false;
					return false;
				}
			}
			if (is_variable(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
				if (lexems[count].lex_code == 59) {
					while (strcmp(parser_tree->current_node->name, "<statement>") != 0) {
						parser_tree->level_up();
					}
					parser_tree->add(lexems[count].name, lexems[count].lex_code);
					parser_tree->level_up();
					while (strcmp(parser_tree->current_node->name, "<statements-list>") != 0) {
						parser_tree->level_up();
					}
					parser_tree->current_node = parser_tree->current_node->descendants[1];
					count++;
					return true;
				}
				else {
					sprintf(temp, "Parser: Error (line %d, column %d): ';' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
					fprintf(file1, "%s \n", temp);
					pars_res = false;
					return false;
				}
			}
			sprintf(temp, "Parser: Error (line %d, column %d): '<expression>' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
			fprintf(file1, "%s \n", temp);
			pars_res = false;
			return false;
		}
		sprintf(temp, "Parser: Error (line %d, column %d): ':=' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
		fprintf(file1, "%s \n", temp);
		pars_res = false;
		return false;
	}
	strcpy(temp, "<empty>");
	parser_tree->add(temp, 0);	
	return false;
}


bool end_check(vector<tokens> lexems) {
	for (int i = 0; i < lexems.size(); i++) {
		if (lexems[i].lex_code == 403)
			return true;
	}
	return false;
}

bool point_check(vector<tokens> lexems) {
	for (int i = 0; i < lexems.size(); i++) {
		if (lexems[i].lex_code == 46)
			return true;
	}
	return false;
}


bool parser(const char* str, vector<data_key> key_words, vector<data_key> identificators, vector<data_key> constants, vector<data_key> delimitors_comp, vector<data_key> delimitors, vector<tokens> lexems) {
	pars_res = true;
	parser_tree = new Parse_Tree;
	char outp_buf[128];
	strcpy(outp_buf, str);
	strcat(outp_buf, "/generated_pars.txt");
	if ((file1 = fopen(outp_buf, "w")) == NULL) {
		cout << "File for writing can not be opened!\n";
		return false;
	}
	
	int count = 0;

	while (count < lexems.size()) {
		if (lexems[count].lex_code == 401) {
			strcpy(temp, "<signal-program>");
			parser_tree->add(temp, 0);
			strcpy(temp, "<program>");
			parser_tree->add(temp, 0);
			parser_tree->add(lexems[count].name, lexems[count].lex_code);
			parser_tree->level_up();
			count++;
			if (!is_proc_identifier(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
				sprintf(temp, "Parser: Error (line %d, column %d): '<procedure-identifier>' expected but ';' found", lexems[count + 1].row_id, lexems[count + 1].col_id);
				fprintf(file1, "%s \n", temp);
				fclose(file1);
				pars_res = false;
				return false;
			}
			while (strcmp(parser_tree->current_node->name, "<program>") != 0) {
				parser_tree->level_up();
			}
			if (lexems[count].lex_code == 59) {
				parser_tree->add(lexems[count].name, lexems[count].lex_code);
				count++;
				parser_tree->level_up();
				strcpy(temp, "<block>");
				parser_tree->add(temp, 0);
				strcpy(temp, "<variable-declarations>");
				parser_tree->add(temp, 0);
				if (lexems[count].lex_code == 404) {
					if (lexems[count+1].lex_code == 402) {
						sprintf(temp, "Parser: Error (line %d, column %d): '<declarations-list>' expected but 'BEGIN' found", lexems[count + 1].row_id, lexems[count + 1].col_id);
						fprintf(file1, "%s \n", temp);
						pars_res = false;
						return false;
					}
					parser_tree->add(lexems[count].name, lexems[count].lex_code);
					count++;
					parser_tree->level_up();
					strcpy(temp, "<declarations-list>");
					parser_tree->add(temp, 0);
					int counter = 0;
					while (is_declaration(key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
						counter++;
						if (lexems[count - 1].lex_code != 59) {
							sprintf(temp, "Parser: Error (line %d, column %d): ':' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
							fprintf(file1, "%s \n", temp);
							pars_res = false;
							return false;
						}
						
					}
					if (pars_res == false) {
						fclose(file1);
						return false;
					}
					if (counter == 0) {
						sprintf(temp, "Parser: Error (line %d, column %d): '<declarations-list>' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
						fprintf(file1, "%s \n", temp);
						fclose(file1);
						return false;
					}
					strcpy(temp, "<empty>");
					parser_tree->add(temp, 0);
				}
				else {
					strcpy(temp, "<empty>");
					parser_tree->add(temp, 0);
					int i = 0;
					while (i < 3) {
						parser_tree->level_up();
						i++;
					}
				}
					
			}
			if (lexems[count].lex_code == 402) {
				while (strcmp(parser_tree->current_node->name, "<block>") != 0) {
					parser_tree->level_up();
				}
				if (!end_check(lexems)) {
					sprintf(temp, "Parser: Error (line %d, column %d): 'END' expected but not found", lexems[lexems.size() - 1].row_id, lexems[lexems.size() - 1].col_id);
					fprintf(file1, "%s \n", temp);
					pars_res = false;
					return false;
				}
				if (!point_check(lexems)) {
					sprintf(temp, "Parser: Error (line %d, column %d): '.' expected but not found", lexems[lexems.size() - 1].row_id, lexems[lexems.size() - 1].col_id);
					fprintf(file1, "%s \n", temp);
					pars_res = false;
					return false;
				}
				parser_tree->add(lexems[count].name, lexems[count].lex_code);
				parser_tree->level_up();
				strcpy(temp, "<statements-list>");
				parser_tree->add(temp, 0);
				strcpy(temp, "<statement>");
				parser_tree->add(temp, 0);
				parser_tree->level_up();
				strcpy(temp, "<statements-list>");
				parser_tree->add(temp, 0);
				parser_tree->level_up();
				parser_tree->current_node = parser_tree->current_node->descendants[0];
				count++;
				key_2 = 0;
				while (is_statement(0, key_words, identificators, constants, delimitors_comp, delimitors, lexems, count)) {
					key_2 = 0;
				}
				if (pars_res == false) {
					fclose(file1);
					return false;
				}
			}
			else {
				sprintf(temp, "Parser: Error (line %d, column %d): 'BEGIN' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
				fprintf(file1, "%s \n", temp);
				pars_res = false;
				return false;
			}
			if (lexems[count].lex_code == 403) {
				while (strcmp(parser_tree->current_node->name, "<block>") != 0) {
					parser_tree->level_up();
				}
				parser_tree->add(lexems[count].name, lexems[count].lex_code);
				parser_tree->level_up();
				parser_tree->level_up();
				count++;
				if (lexems[count].lex_code == 46) {
					parser_tree->add(lexems[count].name, lexems[count].lex_code);
					count++;
					parser_tree->print(file1);
					code_generator(parser_tree, str, lexems);
					return true;
				}
				else {
					sprintf(temp, "Parser: Error (line %d, column %d): '.' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
					fprintf(file1, "%s \n", temp);
					pars_res = false;
					return false;
				}
			}
			else {
				sprintf(temp, "Parser: Error (line %d, column %d): 'END' expected but not found", lexems[count + 1].row_id, lexems[count + 1].col_id);
				fprintf(file1, "%s \n", temp);
				pars_res = false;
				return false;
			}
		}
		sprintf(temp, "Parser: Error (line %d, column %d): 'PROGRAM' expected but not found", 1, 1);
		fprintf(file1, "%s \n", temp);
		delete[] parser_tree;
		pars_res = false;
		return false;
	}

	return true;
}