#if CHANGED

/* exit_main.c
 *	Simple program to test the retun of the main.
 *
 *	Print the char 'a' and then return 2500.
 *
 * 	NOTE: If the main doens't return, the behaviour is unpredictable.
 */


#include "syscall.h"

int main()
{
  return 2500; //Test for "main"'s return value, Exit with EXIT_CODE 2500

}

#endif // CHANGED
