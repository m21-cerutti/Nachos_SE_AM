#if CHANGED

/* userpages0.c
 *	Simple program to test the system call void PutString(char* s).
 *
 *	Put first on console "Hello world!\n", then on a second call "How are you ?".
 *
 * 	NOTE:
 */

#include "syscall.h"

int main()
{
  PutString("Hello world!\n");
  PutString("How are you ?\n");

  return 0;
}

#endif // CHANGED
