#if CHANGED

#include "syscall.h"

int main()
{
  PutString("Hello world!");
  char question[]= "How are you ?";
  PutString(question);
  return 0;
}

#endif // CHANGED
