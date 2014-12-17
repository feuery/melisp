#include <atom_node.h>
#include <string>

using std::string;

const char* atom_node::eval()
{
  string toret = "ATOM: ";
  toret += src;
  return toret.c_str();
}
