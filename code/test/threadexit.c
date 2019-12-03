#if CHANGED

/* threadexit.c
 *	Simple function to test the deletetion of the main thread without interrupting the child.
 *
 *	Print t one thousand time for the son, f -\n for the father and the ftwo call ThreadExit.
 *
 */

#include "syscall.h"

void FonctionThreads(void *arg)
{
  int i = 0;
  for (; i < 1000; i++)
    PutChar('t');

  ThreadExit();
}

#include "syscall.h"

int main()
{
  void *null;
  if (ThreadCreate(FonctionThreads, null) != 0)
  {
    return -1;
  }
  PutChar('f');
  PutChar('\n');
  ThreadExit();
  //never reach
  return -2;
}

#endif // CHANGED
