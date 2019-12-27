#if CHANGED

/* forkstess_func.c
 *	Simple program to stess the system with the creation of multiple threads.
 *
 *	Do the creation of multiple threads that print a character and exit.
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
   for (i = 0; i < NB_THREAD; i++)
   {
      ThreadCreate(f, i);
   }

   ThreadExit();
}

#endif // CHANGED
