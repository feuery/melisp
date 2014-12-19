#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <node.h>
#include <LEAVE_TYPE.h>

class list_node: public node{
public:
  list_node(const char* src);
  ~list_node() { }

  string eval();
private:
  
};

#endif //LIST_NODE_H
