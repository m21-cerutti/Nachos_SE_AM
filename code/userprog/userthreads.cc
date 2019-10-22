#ifdef CHANGED

#include "userthreads.h"

int do_ThreadCreate(int f, int arg)
{
  DEBUG('x', "Initialise User Thread.\n");
  Thread *newThread = new Thread ("ThreadCreated");
  Threads_Struct* threads_struct = new Threads_Struct();
  threads_struct->f = f;
  threads_struct->arg = arg;
  newThread->space = currentThread->space;
  newThread->Start(StartUserThread, threads_struct);
}

void do_ThreadExit(void)
{
  currentThread->Finish();
}

static void StartUserThread(void* threads_pt)
{
  DEBUG('x', "Start User Thread.\n");
  Threads_Struct* threads_struct= (Threads_Struct*) threads_pt;

  int i;
  for (i = 0; i < NumTotalRegs; i++)
    machine->WriteRegister (i, 0);

  // Initial program counter for the threads, it's the function.
  machine->WriteRegister (PCReg, threads_struct->f);
  DEBUG ('x', "Initializing starting thread with function at 0x%x\n", threads_struct->f);

  // Need to also tell MIPS where next instruction is, because
  // of branch delay possibility
  machine->WriteRegister (NextPCReg, machine->ReadRegister(PCReg) + 4);

  int newStack = currentThread->space->AllocateUserStack();
  machine->WriteRegister (StackReg, newStack);
  DEBUG ('x', "Initializing thread's stack register to 0x%x\n", newStack);

  machine->WriteRegister (4, threads_struct->arg);
  DEBUG ('x', "Initializing first argument register with arg 0x%x\n", threads_struct->arg);

  DEBUG('x', "Delete structure.\n");

  machine->Run();

  delete threads_struct;
}


#endif // CHANGED
