#if CHANGED

/* multithreads.c
 *	Resume.
 *
 *	Do.
 *
 * 	NOTE:
 */

#include "syscall.h"

void FonctionThreads(void* arg)
{
  int nb = (int) arg;
	volatile char a = 48;
	PutChar(a+nb);
  ThreadExit();
}


#include "syscall.h"

int main()
{
  int i = 0;
  for (; i < 10000; i++)
  {
    if(ThreadCreate(FonctionThreads, i) != 0)
    {
      return -1;
    }
  }
  ThreadExit();

  return 0;
}

#endif // CHANGED
