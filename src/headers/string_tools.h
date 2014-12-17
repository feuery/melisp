#ifndef string_tools
#define string_tools

#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);                            
std::vector<std::string> split(const std::string &s, char delim);
std::string substring(const char* string, int index, int stopindex);

#endif
