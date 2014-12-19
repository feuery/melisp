#include <atom_node.h>
#include <string>

string atom_node::eval()
{
  string toret = "ATOM: ";
  toret += src;
  return toret;
}
