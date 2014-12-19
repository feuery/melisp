#ifndef READER_H
#define READER_H

#include<vector>
#include<string>

#include<boost/algorithm/string.hpp>

#include<node.h>

using namespace std;

//You have to free whatever this returns
char* read_source(FILE* f);
string get_first_sexpr(char* code);
// void handle_errors(const char* sexpr, int i, const char* extra = NULL);
vector<node* > reader(string& initial_sexpr);
string to_string(vector<node*>& vec);

#endif //READER_H
