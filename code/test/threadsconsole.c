#if CHANGED

/* threadsconsole.c
 *	Simple program to tesst the use of the console with threads.
 *
 *	Create one threads and print ten times a string depending on it's the father(main) or the son(the thread created).
 *
 * 	NOTE: THe order is not determined.
 */

#include "syscall.h"

void FonctionThreads(void* arg)
{
  int i = 0;
  for ( ; i < 10; i++)
  {
    PutString("Hello, i'm your son !\n");
  }
  ThreadExit();
}


#include "syscall.h"

int main()
{
  int i = 0;
  void* null = 0;

  if(ThreadCreate(FonctionThreads, null) != 0)
  {
    return -1;
  }
  for (; i < 10; i++)
  {
    PutString("I'm your father, hello !\n");
  }
  ThreadExit();
}

#endif // CHANGED
