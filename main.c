#include <stdio.h>
#include <stdlib.h>

//This assumes file pointer is at beginning
long filesize(FILE* f)
{
  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  rewind(f);

  return size;
}

int main(int argc, char** argv)
{
  FILE* f = fopen("/home/feuer/test.lisp", "r");

  if(f)
    {
      long f_size = filesize(f);
      char* buffer = malloc(sizeof(char) * f_size);

      if(!buffer) printf("Muistin varaus kusi, mitä ihmettä?");
      else
	{
	  size_t result = fread(buffer, 1, f_size, f);
	  printf("%s", buffer);
	}
  
      fclose(f);
      free(buffer);
    }

  return 0;
}
