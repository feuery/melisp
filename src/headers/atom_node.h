#ifndef ATOM_NODE_H
#define ATOM_NODE_H

#include <node.h>

class atom_node: public node
{
 public:
 atom_node(const char* source): node(ATOM), src(source) { }

  ~atom_node() { }
  string eval();
 private:
  const char* src;

};

#endif //ATOM_NODE_H
