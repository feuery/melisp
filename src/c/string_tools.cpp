#include <string_tools.h>

#include <cstring>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {     
  std::stringstream ss(s);                                                                             
  std::string item;                                                                                    
  while (std::getline(ss, item, delim)) {                                                              
    elems.push_back(item);                                                                           
  }                                                                                                    
  return elems;                                                                                        
}                                                                                                        
                                                                                                                               
                                                                                                                               
std::vector<std::string> split(const std::string &s, char delim) {                                       
  std::vector<std::string> elems;                                                                      
  split(s, delim, elems);                                                                              
  return elems;                                                                                        
}

std::string substring(const char* string, int index, int stopindex)
{
  int string_len = strlen(string), new_len = stopindex - index;

  if(string_len < new_len || new_len <= 0)
    {
      printf("Length of string (%d) in substring less than stopindex-index (%d)\n", strlen, new_len);
      printf("Or stopindex-index <= 0 (%d)\n", new_len);
      return NULL; 
    }

  char* toret = new char[new_len + 1];
  if(!toret)
    {
      printf("Allocating new buffer in substring failed");
      return NULL;
    }

  for(int i=0; i< new_len; i++)
    {
      toret[i] = string[index+i];
    }

  toret[new_len] = '\0';

  std::string reallyToRet(toret);
  delete[] toret;
  
  return reallyToRet;
}
