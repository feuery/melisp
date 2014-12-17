#include <cstring>
#include <string>
#include <string_node.h>
#include <string_tools.h>

using std::string;

const char* string_node::eval()
{
  string toret = "STRING: ";
  toret += substring(string_literal, 1, strlen(string_literal)-2);

  return toret.c_str();
}
