#if CHANGED

/* multithreads.c
 *	Simple program to test the creation of many threads.
 *
 *	Create 26 threads and attribute a alphabetical letter and print it to the console. Can have more than 26 threads but it repeat letters.
 *
 * 	NOTE: The choice is to wait until we can create thread in the system.
 */

#include "syscall.h"

void FonctionThreads(void* arg)
{
  int nb = (int) arg;
	volatile char a = 65;
	PutChar((a+nb)%26 + a);
  ThreadExit();
}


#include "syscall.h"

int main()
{
  int i = 0;
  for (; i < 26; i++)
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
