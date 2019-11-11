#if CHANGED

/* stressthreadstack.c
*	Simple thread to test the corruption of the stack of other threads.
*
*	Create a thread that create a variable in the function called. The main call an otherfonction recursively
*	and when the variable created of the main replace the one of the threads before the stack overflow, the son exit and print normally
* 	"Memory Corrupted.\n".
* 	The fact is the machine halting without printing and errors due to corruption. Uncomment a line change the behaviour.
*
*/

#include "syscall.h"


void FonctionThreads(void* arg)
{
	volatile int i = (int) arg;
	while(i == 0)
	{
		int k;
		for (k=0; k<i; k++){
			PutChar('1');
		}
	}
	PutString("Memory Corrupted.\n");
	ThreadExit();
}

void FonctionMain(void* arg)
{
	volatile int i = (int) arg;
	i++;
	FonctionMain(i);
	//PutChar('0'); // This instruction change behaviour (without hypothesis : function corrupt stack or registers).
	ThreadExit(); //never reached normally
}


#include "syscall.h"

int main()
{
	if(ThreadCreate(FonctionThreads, 0) != 0)
	{
		return -1;
	}
	FonctionMain( 1 );

	return 0;
}

#endif // CHANGED
