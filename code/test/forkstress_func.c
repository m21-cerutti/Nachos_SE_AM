#if CHANGED

/* forkstess_func.c
 *	Simple program to test the system call char ForkExec().
 *
 *	Do
 *
 * 	NOTE: 
 */

#include "syscall.h"

#define NB_THREAD 12

void f(int nb_process)
{
   char c = 'a';
   PutChar(c + nb_process);
   ThreadExit();
} 

int main()
{
   int i;
   for(i=0; i<NB_THREAD; i++)
   {
       ThreadCreate(f, i);
   }

   ThreadExit();
}

#endif // CHANGED
