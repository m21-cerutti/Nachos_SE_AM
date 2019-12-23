#if CHANGED

/* userpages1.c
 *	Brief.
 *
 *	Do
 *
 * 	NOTE:
 */

#include "syscall.h"

#define THIS "aaa\0"

#define THAT "bbb\0"

const int N = 10; // Choose it large enough!

void puts(const char*s)
{
   const char*p;
   for (p = s;*p != '\0'; p++) 
	PutChar(*p);
}

void f(void*arg)
{
   const char*s = arg;
   int i;
   for (i = 0; i < N; i++)
	puts(s);
   ThreadExit();
}

int main()
{
   ThreadCreate(f, THIS);
   f(THAT);
   ThreadExit();
}


#endif // CHANGED
