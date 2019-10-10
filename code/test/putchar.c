#include "syscall.h"

/* puchar.c
 *	Simple program to test the system call void Puchar(char c).
 *
 *	Print the character 'a' and the 3 next characters with a loop. Then put an '\n' character.
 *
 */


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
  print('a',4);
  Halt();
}
