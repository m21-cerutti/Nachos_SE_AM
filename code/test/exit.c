#if CHANGED

/* exit.c
 *	Simple program to test the exit system call.
 *
 * 	NOTE: Use the debug optiion "-d -s" to know the exit code, must be -1.
 */

#include "syscall.h"

int main()
{
  Exit(-1);
}

#endif // CHANGED
