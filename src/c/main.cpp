#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>

#include <boost/algorithm/string.hpp>
#include <vector>

#include <string_tools.h>

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

string substring(const char* string, int index, int stopindex)
{
  int string_len = strlen(string), new_len = stopindex - index;

  if(string_len < new_len || new_len <= 0)
    {
      printf("Length of string (%d) in substring less than stopindex-index (%d)\n", strlen, new_len);
      printf("Or stopindex-index <= 0 (%d)\n", new_len);
      return NULL; 
    }

  char* toret = new char[new_len + 1];
  if(!toret)
    {
      printf("Allocating new buffer in substring failed");
      return NULL;
    }

  for(int i=0; i< new_len; i++)
    {
      toret[i] = string[index+i];
    }

  toret[new_len] = '\0';

  std::string reallyToRet(toret);
  delete[] toret;
  
  return reallyToRet;
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

enum LEAVE_TYPE
  {
    ATOM,
    LIST
  };

vector<std::pair<LEAVE_TYPE, string> > reader(string& initial_sexpr)
{

  if(initial_sexpr.length() == 0) return vector<std::pair<LEAVE_TYPE, string>>();

  int len = initial_sexpr.length();
    string sexpr = substring(initial_sexpr.c_str(), 1, len-1);

  vector<std::pair<LEAVE_TYPE, string>> list;

  int pointer = 0,
    braces_open = 0;

  bool in_word = false;

  for(int i=0; i<len; i++)
    {
      if(sexpr[i] != ' ') in_word = true;

      if(!in_word)
	i++;
      else
	{
	  LEAVE_TYPE type = sexpr[i] == '(' ? LIST:ATOM;

	  if(type == ATOM)
	    {
	      do
		{
		  i++;
		  if(i>=len) goto end;
		} while(sexpr[i] != ' ');
	    }
	  else
	    {
	      braces_open++;
	      do
		{
		  i++;
		  if(i>=len) goto end;

		  if(sexpr[i] == '(') braces_open++;
		  if(sexpr[i] == ')') braces_open--;
		}while(braces_open>0);		  
	    }
	  list.push_back(std::pair<LEAVE_TYPE, string>(type, substring(sexpr.c_str(), pointer, i)));
	  pointer = i;

	  in_word = false;
	}
    }

 end: //Shame on me
  
  return list;
}

string to_string(vector<pair<LEAVE_TYPE, string>>& vec)
{
  string buffer;
  for(unsigned int i=0; i<vec.size(); i++)
    {
      buffer += (vec.at(i).first == ATOM? "Atom: ": "List: ");
      buffer += vec.at(i).second;
      buffer += "\n";
    }

  return buffer;
}

int main(int argc, char** argv)
{
  FILE* f = fopen("/home/feuer/test.lisp", "r");

  char* source = read_source(f);

  string first_sexpr = get_first_sexpr(source);

  vector<pair<LEAVE_TYPE, string>> ast = reader(first_sexpr);
  
  printf(to_string(ast).c_str());

  delete[] source;
  fclose(f);

  return 0;
}
