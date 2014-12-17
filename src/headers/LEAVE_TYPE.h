#ifndef LEAVE_TYPE_H
#define LEAVE_TYPE_H
enum LEAVE_TYPE
  {
    ATOM,
    LIST,
    STRING
  };

inline const char* leave_to_string(LEAVE_TYPE t)
{
  return t == ATOM? "Atom": t == LIST? "List": t == STRING? "String": "Unknown leave_type";
}

#endif //LEAVE_TYPE_H
