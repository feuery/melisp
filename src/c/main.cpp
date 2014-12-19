// #include <cstdio>
// #include <cstdlib>
// #include <cstring>

#include <string>
#include <vector>
#include <iostream>

#include <string_tools.h>

#include <reader.h>

using namespace std;


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
