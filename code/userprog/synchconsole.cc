#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore* readAvail;
static Semaphore* writeDone;

static Semaphore* accessConsole;

static void ReadAvailHandler(void* arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void* arg) { (void) arg; writeDone->V(); }

SynchConsole::SynchConsole(const char* in, const char* out)
{
  readAvail = new Semaphore("read avail", 0);
  writeDone = new Semaphore("write done", 0);
  console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, 0);
  accessConsole = new Semaphore("access console", 1);
}

SynchConsole::~SynchConsole()
{
  delete console;
  delete writeDone;
  delete readAvail;
  delete accessConsole;
}

void SynchConsole::SynchPutChar(int ch)
{
  accessConsole->P();
  console->PutChar(ch);
  writeDone->P();
  accessConsole->V();
}

int SynchConsole::SynchGetChar()
{
  accessConsole->P();
  readAvail->P ();
  int c = console->GetChar ();
  accessConsole->V();
  return c;
}

void SynchConsole::SynchPutString(const char s[])
{
  accessConsole->P();
  if (s != NULL)
  {
    int i = 0;
    while(s[i]!= '\0'){
      console->PutChar(s[i]);
      writeDone->P();
      i++;
    }
  }
  accessConsole->V();
}

void SynchConsole::SynchGetString(char* s, int n)
{
  accessConsole->P();
  if (s != NULL)
  {
    int c = 0;
    int i = 0;
    for(; c != EOF && i < n-1 && c != '\n'; i++){
      readAvail->P ();
      c = console->GetChar();
      s[i] = (char)c;
    }
    s[i] = '\0';
  }
  accessConsole->V();
}

#endif // CHANGED
