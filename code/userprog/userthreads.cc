#ifdef CHANGED

#include "userthreads.h"

static void StartUserThread(void* threads_pt)
{
  DEBUG('c', "Start User Thread.\n");
  Threads_Struct* threads_struct= (Threads_Struct*) threads_pt;

  int i;
  for (i = 0; i < NumTotalRegs; i++)
    machine->WriteRegister (i, 0);

  // Initial program counter for the threads, it's the function.
  machine->WriteRegister (PCReg, threads_struct->f);
  DEBUG ('c', "Initializing starting thread with function at 0x%x\n", threads_struct->f);

  // Need to also tell MIPS where next instruction is, because
  // of branch delay possibility
  machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);

  int newStack = currentThread->space->AllocateUserStack();
  machine->WriteRegister (StackReg, newStack);
  DEBUG ('c', "Initializing thread's stack register to 0x%x\n", newStack);

  machine->WriteRegister (4, threads_struct->arg);
  DEBUG ('c', "Initializing first argument register with arg 0x%x\n", threads_struct->arg);

  machine->Run();

  DEBUG('c', "Delete structure.\n");
  delete threads_struct;
}

int do_ThreadCreate(int f, int arg)
{
  DEBUG('c', "Initialise User Thread.\n");
  try
  {
    Thread *newThread = new Thread ("ThreadChild");
    Threads_Struct* threads_struct = new Threads_Struct();
    threads_struct->f = f;
    threads_struct->arg = arg;
    newThread->space = currentThread->space->CopySpace();
    newThread->Start(StartUserThread, threads_struct);
  }
  catch(int e)
  {
      DEBUG('c', "Initialise User Thread have failed, out of memory !\n");
      return -1;
  }
  return 0;
}

void do_ThreadExit(void)
{
  DEBUG ('c', "Exit the thread.\n");
  int lastThreads = currentThread->space->DeleteUserStack();
  if(lastThreads == 0)
  {
    DEBUG ('c', "Last thread of processus, Shutdown.\n");
    interrupt->Halt ();
  }
  currentThread->Finish();
}



#endif // CHANGED
