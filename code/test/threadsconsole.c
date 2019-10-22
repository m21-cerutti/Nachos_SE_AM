#if CHANGED

/* threadsconsole.c
 *	Resume
 *
 *	Do
 *
 * 	NOTE:
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
  while(1);

  return 0;
}

#endif // CHANGED
