#if CHANGED

/* makethreads.c
 *	Resume
 *
 *	Do
 *
 * 	NOTE:
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
  PutChar('f');
  PutChar('\n');
  while(1);

  //printf("Father\n");
  return 0;
}

#endif // CHANGED
