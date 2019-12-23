#ifdef CHANGED

#include "userforks.h"

static void StartUserFork(void *)
{
    DEBUG('f', "Start User Fork.\n");
    currentThread->space->InitRegisters(); // set the initial register values
    currentThread->space->RestoreState();  // load page table register
    machine->Run();                        // jump to the user progam
}

int do_ForkCreate(char *filename)
{

    DEBUG('f', "Open file User Fork.\n");
    OpenFile *executable = fileSystem->Open(filename);
    if (executable == NULL)
    {
        SetColor(stdout, ColorRed);
        SetBold(stdout);
        printf("Unable to open file %s\n", filename);
        ClearColor(stdout);
        return -2;
    }
    AddrSpace *space = new AddrSpace(executable);
    delete executable; // close file

    DEBUG('f', "Initialise User Fork.\n");
    try
    {
        Thread *newThread = new Thread("ForkChild");
        newThread->space = space;
        newThread->Start(StartUserFork, NULL);
    }
    catch (int e)
    {
        DEBUG('c', "Initialise User Fork have failed, out of memory !\n");
        return -1;
    }
    return 0;
}

#endif // CHANGED
