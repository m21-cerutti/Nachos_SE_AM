#if CHANGED

/* threadsacessotherstack.c
 *	Simple programm to test the access to an other thread's stack.
 *
 *	Create a thread that call a function, the main call it too, that give a pointer to a variable from the thread in a global variable if the son,
 *	ele the main when the global variable is set try to access to it and change it.
 *	If it succeed, the thread print memory corrupted, else it's an infinite loop.
 *
 * 	NOTE: before entering the loop, son and father print 0 and 1 respectively.
 */

#include "syscall.h"

volatile int* accessOtherStack = 0;

void FonctionThreads(void* arg)
{
	volatile int i = (int) arg;
	if(i == 0)
	{
		accessOtherStack = &i;
		PutChar('1');
		while(i == 0); //Normally error from the machine and don't reach the next instructions
		PutString("Memory corrupted.");
	}
	else
	{
		PutChar('0');
		while(accessOtherStack == 0);
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
