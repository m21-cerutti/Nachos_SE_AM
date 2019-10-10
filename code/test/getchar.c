#if CHANGED

/* getchar.c
 *	Simple program to test the system call char GetChar(). If the end of file is attend return EOF.
 *
 *	Wait for an character input, then get the character, increment it and put again to verify the result.
 *
 * 	NOTE: the variable c must be initialised for debug memory, and before any other intructions
 *   otherwise it make make errors with the debug (can be commented in progtest.c).
 */

#include "syscall.h"

int main()
{
  char c = 0;
  c = GetChar();
  c++;
  PutChar(c);

  return 0;
}

#endif // CHANGED
