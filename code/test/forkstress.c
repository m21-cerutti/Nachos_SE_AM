#if CHANGED

/* fork.c
 *	Simple program to stress the system with the creation of new processus with Fork.
 *
 *	Do the creation of forked processus, for stress of threads. Permit to cumulate the two tests.
 */

#include "syscall.h"

#define NB_PROCESS 12

int main()
{
    int i;
    for (i = 0; i < NB_PROCESS; i++)
    {
        ForkExec("../test/threadstress_forkfunc");
    }
}

#endif // CHANGED
