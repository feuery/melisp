#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>

#include <boost/algorithm/string.hpp>
#include <vector>
#include <iostream>

#include <string_tools.h>
#include <atom_node.h>
#include <list_node.h>
#include <string_node.h>

using namespace std;

//This assumes file pointer is at beginning
long filesize(FILE* f)
{
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  rewind(f);

  return size;
}

//You have to free whatever this returns
char* read_source(FILE* f)
{
  if(f)
    {
      long f_size = filesize(f);
      char* buffer = new char[f_size];

      if(!buffer)
	return NULL;
      else
	{
	  fread(buffer, 1, f_size, f);
	  return buffer;
	}
    }

  return NULL;
}

string get_first_sexpr(char* code)
{
  int pointer = 0, length = strlen(code);
  int index_of_open_brace = -1,
    index_of_closing_brace = -1,
    braces_opened = 0;
  

  for(; pointer<length; pointer++)
    {
      if(code[pointer] == '(' && index_of_open_brace == -1)
	{
	  index_of_open_brace = pointer;
	}

      if(code[pointer] == '(' && index_of_open_brace != -1) braces_opened++;
      if(code[pointer] == ')' && index_of_open_brace != -1) braces_opened--;
      

      if(code[pointer] == ')' && index_of_open_brace != -1 && braces_opened == 0)
	{
	  index_of_closing_brace = pointer;
	  break;
	}
    }

  return substring(code, index_of_open_brace, index_of_closing_brace + 1);
}

void handle_errors(const char* sexpr, int i, const char* extra = NULL)
{
  if(sexpr[i] == '\n' || sexpr[i] == '\t')
    {
      printf("You have invalid chars at %d\n", i);
      if(extra != NULL) printf("%s\n", extra);
    }
}

vector<node* > reader(string& initial_sexpr)
{
  if(initial_sexpr.length() == 0) return vector<node*>();

  int len = initial_sexpr.length();
  string sexpr = substring(initial_sexpr.c_str(), 1, len-1);

  vector<node*> list;
  
  int pointer = 0,
    braces_open = 0;

  bool in_word = false;
  int i = 0;

  while(i<len)
    {
      char first = sexpr[i];
      
      in_word = !(first == ' ' ||
		  first == ')' ||
		  first == '\n' ||
		  first == '\r' ||
		  first == '\t' );

      if(!in_word)
	{
	  i++;
	}
      else
	{
	  pointer = i;
	  LEAVE_TYPE type = sexpr[i] == '(' ? LIST:
	    sexpr[i]=='"'?STRING:ATOM;
	  	  
	  if(type == ATOM)
	    {
	      do
		{
		  handle_errors(sexpr.c_str(), i, "calling at ATOM branch");
		  i++;
		  if(i>=len) goto end;

		  if(sexpr[i] == '\n' || sexpr[i] == '\t') printf("You have invalid chars at %d\n", i);
		} while(sexpr[i] != ' ');
	    }
	  else if(type == STRING)
	    {
	      do
		{
		  handle_errors(sexpr.c_str(), i, "Calling at STRING_branch");
		  i++;
		  if(sexpr[i] == '\\' && sexpr[i+1] == '"') i++;
		} while(sexpr[i] != '"');
	    }
	  else
	    {
	      braces_open++;
	      do
		{
		  handle_errors(sexpr.c_str(), i, "calling at LIST branch");
		  i++;
		  if(i>=len) goto end;

		  if(sexpr[i] == '(') braces_open++;
		  if(sexpr[i] == ')') braces_open--;
		}while(braces_open>0);		  
	    }
	  i++;
	  string subst = substring(sexpr.c_str(), pointer, i);
	  
	  list.push_back(type == ATOM?
			 (node*) new atom_node(subst.c_str()):
			 type == STRING ?
			 (node*) new string_node(subst.c_str()):
			 type == LIST ?
			 (node*) new list_node(subst.c_str()) :
			 (node*)new string_node("\"Unknown node\""));
	  // printf("Stopped a word at %d, substring(%d, %d) is %s\n", pointer, pointer, i, subst.c_str());

	  in_word = false;

	}
    }

 end: //Shame on me
  
  return list;
}

string to_string(vector<node*>& vec)
{
  string buffer;
  for(unsigned int i=0; i<vec.size(); i++)
    {
      LEAVE_TYPE type = vec.at(i)->type();
      buffer += vec.at(i)->eval();
      buffer += "\n";
    }

  return buffer;
}

int main(int argc, char** argv)
{
  FILE* f = fopen("/home/feuer/test.lisp", "r");

  char* source = read_source(f);

  string first_sexpr = get_first_sexpr(source);

  vector<node*> ast = reader(first_sexpr);
  
  printf(to_string(ast).c_str());

  for(node* nd: ast) delete nd;

  delete[] source;
  fclose(f);

  return 0;
}
