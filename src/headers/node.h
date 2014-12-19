#ifndef NODE_H
#define NODE_H

#include <LEAVE_TYPE.h>
#include <string>

using std::string;

class node{
 public:

 node(LEAVE_TYPE type): _type(type) { }
  virtual ~node() { }

  LEAVE_TYPE type() { return _type; }
  
  virtual string eval() = 0;
  
 private:

  LEAVE_TYPE _type;
  
};

#endif //NODE_H
