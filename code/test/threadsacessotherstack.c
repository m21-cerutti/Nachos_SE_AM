#if CHANGED

/* multithreads.c
 *	Resume.
 *
 *	Do.
 *
 * 	NOTE:
 */

#include "syscall.h"

volatile int* accessOtherStack = 0;

void FonctionThreads(void* arg)
{
	volatile int i = (int) arg;
	if(i == 0)
	{
		accessOtherStack = &i;
		while(i == 0) PutChar('1'); //Normally error from the machine and don't reach the next instructions
		PutString("Memory corrupted.");
	}
	else
	{
		while(accessOtherStack == 0) PutChar('0');
		*accessOtherStack = *accessOtherStack +1;
	}
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
