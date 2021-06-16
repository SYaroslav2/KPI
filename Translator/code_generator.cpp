#define _CRT_SECURE_NO_WARNINGS
#include "code_generator.h"
#include "fstream"

using namespace std;

struct var {
	char name[25];
	char type[5];
	char var_type[25];
};

struct loop_labels {
	char name[25];
};

struct error_place {
	int col;
	int row;
};

var tmp;
loop_labels* lbl;
vector<const char*> non_terminal_d_0 = { "<signal-program>", "<variable-identifier>", "<procedure-inentifier>", "<inentifier>" };
vector<loop_labels*> labels;
vector<const char*> registers = {"AX", "BX", "CX", "DX"};
vector<const char*> del_registers;

bool in_d_0(char str[]) {
	for (int i = 0; i < non_terminal_d_0.size(); i++) {
		if (strcmp(str, non_terminal_d_0[i]) == 0)
			return true;
	}
	return false;
}

bool in_variable(char str[], char str_type[], vector<var>& variables) {
	for (int i = 0; i < variables.size(); i++) {
		if (strcmp(str, variables[i].name) == 0) {
			strcpy(str_type, variables[i].var_type);
			return true;
		}
	}
	return false;
}

void in_lexems(vector<tokens> lexems, char str[], int& col, int& row) {
	int count = 0;
	for (int i = 0; i < lexems.size(); i++) {
		if (strcmp(str, lexems[i].name) == 0) {
			if (count > 0) {
				col = lexems[i].col_id;
				row = lexems[i].row_id;
				return;
			}
			count++;
		}
	}
	return;
}


void in_lexems_dec(vector<tokens> lexems, char str[], int& col, int& row) {
	for (int i = 0; i < lexems.size(); i++) {
		if (strcmp(str, lexems[i].name) == 0) {
			col = lexems[i].col_id;
			row = lexems[i].row_id;
			return;
		}
	}
	return;
}


void return_reg(const char* str) {
	registers.push_back(str);
	for (int i = 0; i < del_registers.size(); i++) {
		if (strcmp(del_registers[i], str) == 0) {
			del_registers.erase(del_registers.begin() + i);
		}
	}
}

vector<error_place*> arr_error(vector<tokens> lexems, char str[]) {
	int count = 0;
	vector<error_place*> vect;
	
	while (strcmp(lexems[count].name, "BEGIN") != 0) {
		count++;
	}
	count++;
	for (int i = count; i < lexems.size(); i++) {
		if (strcmp(str, lexems[i].name) == 0 && strcmp("[", lexems[i + 1].name) != 0) {
			error_place* err = new error_place;
			err->col = lexems[i].col_id;
			err->row = lexems[i].row_id;
			vect.push_back(err);
		}
	}
	return vect;
}

vector<error_place*> idx_error(vector<tokens> lexems, char str[]) {
	int count = 0;
	vector<error_place*> vect;

	while (strcmp(lexems[count].name, "BEGIN") != 0) {
		count++;
	}
	count++;
	for (int i = count; i < lexems.size(); i++) {
		if (strcmp(str, lexems[i].name) == 0 && strcmp("[", lexems[i + 1].name) == 0) {
			error_place* err = new error_place;
			err->col = lexems[i].col_id;
			err->row = lexems[i].row_id;
			vect.push_back(err);
		}
	}
	return vect;
}

bool is_term(char str[]) {
	if (_strnicmp(str, "<", 1) == 0 || _strnicmp(str, "[", 1) == 0)
		return false;
	return true;
}

void code(Parse_Tree_Node* root, vector<string>&  listing, vector<string>& errors, vector<tokens> lexems, int key, vector<var>& variables, bool& error) {
	string list_line;
	char str[128];
	if (!is_term(root->name)) {
		if (in_d_0(root->name)) {
			code(root->descendants[0], listing, errors, lexems, 3, variables, error);
			return;
		}
		else if (strcmp(root->name, "<program>") == 0) {
			code(root->descendants[3], listing, errors, lexems, 3, variables, error);
			return;
		}
		else if (strcmp(root->name, "<block>") == 0) {
			for (int i = 0; i < root->descendants.size(); i++) {
				if (error)
					return;
				code(root->descendants[i], listing, errors, lexems, 3, variables, error);
			}
			return;
		}
		else if (strcmp(root->name, "<variable-declarations>") == 0) {
			if (strcmp(root->descendants[0]->name, "<empty>") == 0) {
				return;
			}
			else {
				listing.push_back("data\t\tSEGMENT\n");
				code(root->descendants[1], listing, errors, lexems, 3, variables, error);
				listing.push_back("\ndata\t\tENDS\n\n");
				if (error)
					return;
			}
			return;
		}
		else if (strcmp(root->name, "<declarations-list>") == 0) {
			if (strcmp(root->descendants[0]->name, "<empty>") == 0) {
				return;
			}
			else {
				code(root->descendants[0], listing, errors, lexems, 3, variables, error);
				if (error)
					return;
				code(root->descendants[1], listing, errors, lexems, 3, variables, error);
				if (error)
					return;
			}
			return;
		}
		else if (strcmp(root->name, "<declaration>") == 0) {
			char str[128];
			if (in_variable(root->descendants[0]->descendants[0]->descendants[0]->name, str, variables)) {
				int col, row;
				in_lexems(lexems, root->descendants[0]->descendants[0]->descendants[0]->name, col, row);
				sprintf(str, "Code Generator: Error (line %d, column %d): repeated name '%s'", row, col, root->descendants[0]->descendants[0]->descendants[0]->name);
				list_line = str;
				errors.push_back(list_line);
				error = true;
				return;
			}
			else {
				strcpy(tmp.name, root->descendants[0]->descendants[0]->descendants[0]->name);
				code(root->descendants[2], listing, errors, lexems, 3, variables, error);
				if (error)
					return;
			}
			return;
		}
		else if (strcmp(root->name, "<attribute>") == 0) {
			char str[128];
			if (strcmp(root->descendants[0]->name, "[<range>]") == 0) {
				int col, row;
				in_lexems_dec(lexems, tmp.name, col, row);
				sprintf(str, "Code Generator: Error (line %d, column %d): error type(RANGE WITHOUT ANYTHING) for '%s'", row, col, tmp.name);
				list_line = str;
				errors.push_back(list_line);
				error = true;
				return;
			}
			if ((strcmp(root->descendants[0]->name, "INTEGER") == 0 || strcmp(root->descendants[0]->name, "FLOAT") == 0) && strcmp(root->ancestor->descendants[3]->descendants[0]->name, "[<range>]") == 0) {
				if (strcmp(tmp.name, "A") == 0 || strcmp(tmp.name, "B") == 0 || strcmp(tmp.name, "C") == 0 || strcmp(tmp.name, "D") == 0) {
					int col, row;
					in_lexems_dec(lexems, tmp.name, col, row);
					sprintf(str, "Code Generator: Error (line %d, column %d): error type for '%s'", row, col, tmp.name);
					list_line = str;
					errors.push_back(list_line);
					error = true;
					return;
				}

			}
			if (strcmp(root->descendants[0]->name, "INTEGER") == 0) {
				if (strcmp(tmp.name, "A") != 0 && strcmp(tmp.name, "B") != 0) {
					int col, row;
					in_lexems_dec(lexems, tmp.name, col, row);
					sprintf(str, "Code Generator: Error (line %d, column %d): error type(NOT FLOAT) for '%s'", row, col, tmp.name);
					list_line = str;
					errors.push_back(list_line);
					error = true;
					return;
				}
				strcpy(tmp.type, "\t\tdw");
				strcpy(str, tmp.name);
				strcat(str, tmp.type);
				if (strcmp(root->ancestor->descendants[3]->descendants[0]->name, "<empty>") == 0) 
					strcpy(tmp.var_type, "INTEGER");
				else {
					strcpy(tmp.var_type, "ARRAY");
				}
				list_line = str;
				listing.push_back(list_line);
				variables.push_back(tmp);
			}
			if (strcmp(root->descendants[0]->name, "FLOAT") == 0) {
				if (strcmp(tmp.name, "C") != 0 && strcmp(tmp.name, "D") != 0) {
					int col, row;
					in_lexems_dec(lexems, tmp.name, col, row);
					sprintf(str, "Code Generator: Error (line %d, column %d): error type(NOT INTEGER) for '%s'", row, col, tmp.name);
					list_line = str;
					errors.push_back(list_line);
					error = true;
					return;
				}
				if (strcmp(root->ancestor->descendants[3]->descendants[0]->name, "<empty>") == 0) {
					strcpy(tmp.type, "\t\tdd");
					strcpy(tmp.var_type, "FLOAT");
					variables.push_back(tmp);
					strcpy(str, tmp.name);
					strcat(str, tmp.type);
					list_line = str;
					listing.push_back(str);
				}
				else {
					strcpy(tmp.type, "\t\tdw");
					strcpy(tmp.var_type, "ARRAY");
					variables.push_back(tmp);
					strcpy(str, tmp.name);
					strcat(str, tmp.type);
					list_line = str;
					listing.push_back(str);
				}
			}
			
			
			return;
		}
		else if (strcmp(root->name, "<statements-list>") == 0) {
			if (strcmp(root->descendants[0]->name, "<empty>") == 0) {
				char str_state[128];
				strcpy(str_state, "\t\tNOP");
				list_line = str_state;
				listing.push_back(list_line);
			}
			else {
				code(root->descendants[0], listing, errors, lexems, 3, variables, error);
				if (error)
					return;
				code(root->descendants[1], listing, errors, lexems, 3, variables, error);
				if (error)
					return;
			}

		}
		else if (strcmp(root->name, "<statement>") == 0) {
			if (strcmp(root->descendants[0]->name, "LOOP") == 0) {
				char str_state [128];
				char str_jmp [128];
				lbl = new loop_labels;
				sprintf(str_state, "?L%d:", labels.size() + 1);
				strcpy(lbl->name, str_state);
				labels.push_back(lbl);
				listing.push_back(lbl->name);
				code(root->descendants[1], listing, errors, lexems, 3, variables, error);
				str_state[strlen(str_state) - 1] = '\0';
				sprintf(str_jmp, "JMP %s", str_state);
				list_line = str_jmp;
				listing.push_back(list_line);
			}
			else {
				code(root->descendants[2], listing, errors, lexems, 0, variables, error);
				if (error)
					return;
				code(root->descendants[0], listing, errors, lexems, 1, variables, error);
				if (error)
					return;
			}
		}
		else if (strcmp(root->name, "<variable>") == 0) {
			if (in_variable(root->descendants[0]->descendants[0]->descendants[0]->name, str, variables)) {
				if (strcmp(str, "ARRAY") == 0 && strcmp(root->descendants[1]->descendants[0]->name, "<empty>") == 0) {
					vector<error_place*> arr = arr_error(lexems, root->descendants[0]->descendants[0]->descendants[0]->name);
					for (int i = 0; i < arr.size(); i++) {
						char err_str [128];
						sprintf(err_str, "Code Generator: Error (line %d, column %d): using array '%s' name without index ", arr[i]->row, arr[i]->col, root->descendants[0]->descendants[0]->descendants[0]->name);
						list_line = err_str;
						errors.push_back(list_line);
						error = true;
						return;
					}
				}
				else if (strcmp(str, "ARRAY") == 0 && strcmp(root->descendants[1]->descendants[0]->name, "[<expression>]") == 0) {
					strcpy(str, root->descendants[1]->descendants[0]->descendants[0]->name);
					code(root->descendants[1]->descendants[0], listing, errors, lexems, key, variables, error);
					if(key == 0){
						sprintf(str, "\t\tMOV %s, %s[%s]", registers.at(registers.size() - 1), root->descendants[0]->descendants[0]->descendants[0]->name, del_registers.at(del_registers.size() - 1));
						list_line = str;
						listing.push_back(list_line);
						del_registers.push_back(registers.at(registers.size() - 1));
						registers.pop_back();
						return_reg(del_registers.at(del_registers.size() - 2));
					}
					if (key == 1) {
						sprintf(str, "\t\tMOV %s[%s], %s", root->descendants[0]->descendants[0]->descendants[0]->name, del_registers.at(del_registers.size() - 1), del_registers.at(del_registers.size() - 2));
						list_line = str;
						listing.push_back(list_line);
						while (del_registers.size() > 0) {
							return_reg(del_registers.at(0));
						}
					}
				}
				else if ((strcmp(str, "INTEGER") == 0 || strcmp(str, "FLOAT") == 0) && strcmp(root->descendants[1]->descendants[0]->name, "<empty>") != 0) {
					vector<error_place*> arr = idx_error(lexems, root->descendants[0]->descendants[0]->descendants[0]->name);
					for (int i = 0; i < arr.size(); i++) {
						char err_str [128];
						sprintf(err_str, "Code Generator: Error (line %d, column %d): using variable '%s' name with index ", arr[i]->row, arr[i]->col, root->descendants[0]->descendants[0]->descendants[0]->name);
						list_line = err_str;
						errors.push_back(list_line);
						error = true;
						return;
					}
				}
				else {
					if (key == 0) {
						sprintf(str, "\t\tMOV %s, %s", registers.at(registers.size() - 1), root->descendants[0]->descendants[0]->descendants[0]->name);
						list_line = str;
						listing.push_back(list_line);
						del_registers.push_back(registers.at(registers.size() - 1));
						registers.pop_back();
						return;
					}
					if (key == 1) {
						sprintf(str, "\t\tMOV %s, %s", root->descendants[0]->descendants[0]->descendants[0]->name, del_registers.at(del_registers.size() - 1));
						list_line = str;
						listing.push_back(list_line);
						while (del_registers.size() > 0) {
							return_reg(del_registers.at(0));
						}
					}
				}
			}
		}
		else if (strcmp(root->name, "<expression>") == 0 || strcmp(root->name, "[<expression>]") == 0) {
			if (strcmp(root->descendants[0]->name, "<unsigned-integer>") == 0) {
				sprintf(str, "\t\tMOV %s, %s", registers.at(registers.size()-1), root->descendants[0]->descendants[0]->name);
				list_line = str;
				listing.push_back(list_line);
				del_registers.push_back(registers.at(registers.size() - 1));
				registers.pop_back();
				return;
			}
			else {
				code(root->descendants[0], listing, errors, lexems, key, variables, error);
			}
		}
	}
	else {
		if (strcmp(root->name, "BEGIN") == 0) {
			listing.push_back("code\t\tSEGMENT\n\t\t\tASSUME:\tcs:code, ds:data\nbegin:\n");
			return;
		}
		
		if (strcmp(root->name, "END") == 0) {
			listing.push_back("\t\tmov\tax, 4c00h\n\t\tint\t21h\ncode\tENDS\n\t\tend\tbegin");
			return;
		}
	}


	return;
}

void print_code(vector<string> listing, ofstream file1) {
	for (int i = 0; i < listing.size(); i++)
		file1 << listing[i] << endl;
}

bool code_generator(Parse_Tree* tree, const char* str, vector<tokens> lexems) {
	char outp_buf[128];
	ofstream file1;
	vector<string> listing;
	vector<string> errors;
	strcpy(outp_buf, str);
	strcat(outp_buf, "/generated.txt");
	file1.open(outp_buf); 
	vector<var> variables;
	bool error = false;;
	code(tree->root, listing, errors, lexems, 2, variables, error);
	
	if (file1.is_open()) {
		if (errors.size() > 0) {
			for (int i = 0; i < errors.size(); i++)
				file1 << errors[i] << endl;
		}
		else {
			for (int i = 0; i < listing.size(); i++)
				file1 << listing[i] << endl;
		}
	}

	file1.close();
	return false;
}