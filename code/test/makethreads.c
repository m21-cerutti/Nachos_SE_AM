#if CHANGED

/* makethreads.c
 *	Simple program to test the creation and the deletetion of one thread.
 *
 *	The child print a char 's' and then '\n', the father do an active wait.
 *
 * 	NOTE: The program have an infinite loop, use ctrl-c to stop it.
 */

#include "syscall.h"

void FonctionThreads(void* arg)
{
  PutChar('s');
  PutChar('\n');
  ThreadExit();
}


#include "syscall.h"

int main()
{
  void* null;
  if(ThreadCreate(FonctionThreads, null) != 0)
  {
    return -1;
  }

  return 0;
}

#endif // CHANGED
