#ifdef CHANGED

// userthreads.h
//      Define the utilities functions for user threads.
//

#include "system.h"

typedef struct
{
  int f;
  int arg;
} Thread_Struct;

extern int do_ThreadCreate(int f, int arg);

extern void do_ThreadExit(void);

#endif // CHANGED
