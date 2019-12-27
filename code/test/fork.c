#if CHANGED

/* fork.c
 *	Simple program to test the system call char ForkExec().
 *
 *	Do the test userpages0 and userpages1
 *
 * 	NOTE: The processus will exit but the child live, exit is not different from threadexit in this case.
 */

#include "syscall.h"

int main()
{
  ForkExec("../test/userpages0");
  ForkExec("../test/userpages1");

  return 0;
}

#endif // CHANGED
