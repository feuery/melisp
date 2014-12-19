#ifndef STRING_NODE_H
#define STRING_NODE_H

#include <node.h>

class string_node: public node
{
 public:
 string_node(const char* string_literal): node(STRING), string_literal(string_literal) { }
  ~string_node() { }

  string eval();
 private:
  const char* string_literal;

};

#endif //STRING_NODE_H
