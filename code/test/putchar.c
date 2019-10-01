#include "syscall.h"

void print(char c, int n)
{
  int i;

  #if CHANGED

  for (i = 0; i < n; i++) {
  PutChar(c + i);
  }
  PutChar('\n');

  #endif // CHANGED
}

int main()
{
  //Exit(1); //Work like expected
  print('a',4);
  //Halt();
  return 2500; //Not working
}
