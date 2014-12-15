#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
      char* buffer = malloc(sizeof(char) * f_size);

      if(!buffer)
	return NULL;
      else
	{
	  size_t result = fread(buffer, 1, f_size, f);
	  return buffer;
	}
    }

  return NULL;
}

//You need to free this
//Returns NULL on error
char* substring(char* string, int index, int stopindex)
{
  int string_len = strlen(string), new_len = stopindex - index;

  if(string_len < new_len || new_len <= 0)
    {
      printf("Length of string (%d) in substring less than stopindex-index (%d)\n", strlen, new_len);
      printf("Or stopindex-index <= 0 (%d)\n", new_len);
      return NULL; 
    }

  char* toret = malloc(sizeof(char) * (new_len + 1));
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

  return toret;  
}


char* get_first_sexpr(char* code)
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

int main(int argc, char** argv)
{
  FILE* f = fopen("/home/feuer/test.lisp", "r");

  char* source = read_source(f);

  char* first_sexp = get_first_sexpr(source);

  printf("First sexp:\n%s\n", first_sexp);
  
  free(first_sexp);

  free(source);
  
  fclose(f);

  return 0;
}
