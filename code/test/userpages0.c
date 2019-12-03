#if CHANGED

/* userpages0.c
 *	Brief.
 *
 *	Do
 *
 * 	NOTE:
 */

#include "syscall.h"

void print(char c, int n)
{
  int i;
  for (i = 0; i < n; i++)
  {
    PutChar(c + i);
  }
  PutChar('\n');
}

int main()
{
  PutString("Hello world!\n");
  PutString("How are you ?\n");
  print('a', 10);
  while (1)
    ;

  return 0;
}

#endif // CHANGED
