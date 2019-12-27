// progtest.cc
//      Test routines for demonstrating that Nachos can load
//      a user program and execute it.
//
//      Also, routines for testing the Console hardware device.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "console.h"

#ifdef CHANGED
#include "synchconsole.h" //les consignes mettent des chevrons <synchconsole.h>
#endif                    //CHANGED

#include "addrspace.h"
#include "synch.h"

//----------------------------------------------------------------------
// StartProcess
//      Run a user program.  Open the executable, load it into
//      memory, and jump to it.
//----------------------------------------------------------------------

void StartProcess(char *filename)
{
  OpenFile *executable = fileSystem->Open(filename);
  AddrSpace *space;

  if (executable == NULL)
  {
    SetColor(stdout, ColorRed);
    SetBold(stdout);
    printf("Unable to open file %s\n", filename);
    ClearColor(stdout);
    return;
  }
  space = new AddrSpace(executable);
  currentThread->space = space;

  delete executable; // close file

  space->InitRegisters(); // set the initial register values
  space->RestoreState();  // load page table register

#ifdef CHANGED
  // Non initialised variable make errors with debug memory.
  machine->DumpMem("memory.svg");
#else
  machine->DumpMem("memory.svg");
#endif            //CHANGED
  machine->Run(); // jump to the user progam
  ASSERT(FALSE);  // machine->Run never returns;
  // the address space exits
  // by doing the syscall "exit"
}

// Data structures needed for the console test.  Threads making
// I/O requests wait on a Semaphore to delay until the I/O completes.

static Console *console;
static Semaphore *readAvail;
static Semaphore *writeDone;

//----------------------------------------------------------------------
// ConsoleInterruptHandlers
//      Wake up the thread that requested the I/O.
//----------------------------------------------------------------------

static void
ReadAvailHandler(void *arg)
{
  (void)arg;
  readAvail->V();
}
static void
WriteDoneHandler(void *arg)
{
  (void)arg;
  writeDone->V();
}

//----------------------------------------------------------------------
// ConsoleTest
//      Test the console by echoing characters typed at the input onto
//      the output.  Stop when the user types a 'q'.
//----------------------------------------------------------------------

#ifdef CHANGED

void echoChar(Console *cons, const char ch)
{
  if (cons == NULL || writeDone == NULL)
    return;
  if (ch != '\n' && ch != EOF)
  {
    cons->PutChar('<');
    writeDone->P();
    cons->PutChar(ch);
    writeDone->P();
    cons->PutChar('>');
    writeDone->P();
  }
  else
  {
    cons->PutChar('\n');
    writeDone->P();
  }
}
#endif // CHANGED

void ConsoleTest(const char *in, const char *out)
{
  char ch;
  printf("Pour quitter, appuyez sur Ctrl+D\n\n");
  readAvail = new Semaphore("read avail", 0);
  writeDone = new Semaphore("write done", 0);
  console = new Console(in, out, ReadAvailHandler, WriteDoneHandler, 0);

  for (;;)
  {
    readAvail->P(); // wait for character to arrive
    ch = console->GetChar();

#ifdef CHANGED

    echoChar(console, ch);

#else

    console->PutChar(ch); // echo it!
    writeDone->P();       // wait for write to finish

#endif // CHANGED

    if (ch == EOF)
    {

#ifdef CHANGED
      printf("\nAu revoir.\n\n");
#endif // CHANGED

      break; // if q, quit
    }
  }
  delete console;
  delete readAvail;
  delete writeDone;
}

#ifdef CHANGED

void SynchConsoleTest(const char *in, const char *out)
{
  char ch;
  SynchConsole *test_synchconsole = new SynchConsole(in, out);
  while ((ch = test_synchconsole->SynchGetChar()) != EOF)
  {
    test_synchconsole->SynchPutChar('<');
    test_synchconsole->SynchPutChar(ch);
    test_synchconsole->SynchPutChar('>');
    test_synchconsole->SynchPutChar('\n');
  }
  fprintf(stderr, "EOF detected in SynchConsole!\n");

  delete test_synchconsole;
}

#endif //CHANGED
