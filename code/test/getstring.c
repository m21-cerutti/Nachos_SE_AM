#if CHANGED

/* getstring.c
 *	Simple program to test the system call char GetString().
 *
 *	Wait for input user, and put it in the variable buff(same as a buffer).
 *  The input is finished by '\n' if the input size is below the size of the buffer variable,
 *  otherwise thee last index of the buffer is fill with '\0'.
 *  Then the program put the content's buffer to the console with system call PutString.
 *
 *
 * 	NOTE: On the console we need to validate the input with a '\n' to do the system call.
 */

#include "syscall.h"

int main()
{
  char buff[5];
  GetString(buff, 5);
  PutString("\necho :\n");
  PutString(buff);
  return 0;
}

#endif // CHANGED
