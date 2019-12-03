#if CHANGED

/* mainargs.c
 *	Simple program to test ...
 *
 *	Do
 *
 * 	NOTE: 
 */

#include "syscall.h"

int main(int argc, char **argv)
{
    int i;
    PutString("./");
    for (i = 0; i < argc; i++)
    {
        PutString(argv[i]);
        PutString(" ");
    }
    PutString("\n");
    return 0;
}

#endif // CHANGED