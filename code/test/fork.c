#if CHANGED

/* fork.c
 *	Simple program to test the system call char ForkExec().
 *
 *	Do
 *
 * 	NOTE: 
 */

#include "syscall.h"

int main()
{
    ForkExec("../test/userpages0");
    ForkExec("../test/userpages1");

  return 0;
}

#endif // CHANGED
