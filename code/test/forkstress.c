#if CHANGED

/* fork.c
 *	Simple program to test the system call char ForkExec().
 *
 *	Do
 *
 * 	NOTE: 
 */

#include "syscall.h"

#define NB_PROCESS 12

int main()
{
   int i;
   for(i=0; i<NB_PROCESS; i++)
   {
       ForkExec("../test/forkstress_func");
   }
}

#endif // CHANGED
