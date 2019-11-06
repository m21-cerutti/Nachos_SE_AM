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
	int i = (int) arg;
	while(i == 0)
	{
		int k;
		for (k=0; k<i; k++)
			PutChar('1');
	}
	i++;
	FonctionThreads(i);

  ThreadExit();
}


#include "syscall.h"

int main()
{
  if(ThreadCreate(FonctionThreads, 0) != 0)
  {
    return -1;
  }
	FonctionThreads( 1 );

  return 0;
}

#endif // CHANGED
