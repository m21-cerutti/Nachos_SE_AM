// exception.cc
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

#ifdef CHANGED
#include "userthreads.h"
#endif // CHANGED

//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions
//      are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler (ExceptionType which)
{
    int type = machine->ReadRegister (2);

    switch (which)
      {
	case SyscallException:
          {
	    switch (type)
	      {
		case SC_Halt:
		  {
		    DEBUG ('s', "Shutdown, initiated by user program.\n");
		    interrupt->Halt ();
		    break;
		  }

      #ifdef CHANGED

    case SC_PutChar:
      {
        char c = (char) machine->ReadRegister (4);
  		  DEBUG ('s', "Put a char %c, initiated by user program.\n", c);
        synchconsole->SynchPutChar(c);
        break;
      }

      case SC_Exit:
      {
        int exit_code = (int) machine->ReadRegister(4);
        DEBUG ('s', "Exit with code %d and shutdown, initiated by user program.\n", exit_code);
        machine->WriteRegister(2, exit_code);
        interrupt->Halt ();
        break;
      }

      case SC_PutString:
      {
        int str = (int) machine->ReadRegister (4);

        accessBuffer->P();
  		  DEBUG ('s', "Put a string, initiated by user program.\n");
        int totalWritten = 0;
        int nbWritten = MAX_STRING_SIZE-1;
        while( nbWritten == MAX_STRING_SIZE-1)
        {
          nbWritten = copyStringFromMachine(str+totalWritten, bufferSystem, MAX_STRING_SIZE);
    		  DEBUG ('s', "%d character written.\n", nbWritten);
          synchconsole->SynchPutString(bufferSystem);
          totalWritten += nbWritten;
        }
  		  DEBUG ('s', "%d character written total.\n", totalWritten);
        accessBuffer->V();
        break;
      }

      case SC_GetChar:
      {
        int str = synchconsole->SynchGetChar();
  		  DEBUG ('s', "Get char \"%c\", initiated by user program.\n", str);
        if(str == EOF){
            machine->WriteRegister(2, '\0');
            DEBUG('s', "End of file attend.\n");
        }
        else
          machine->WriteRegister(2, str);
        break;
      }

      case SC_GetString:
      {
        int addr = (int) machine->ReadRegister (4);
        int size = (int) machine->ReadRegister (5);

        accessBuffer->P();
  		  DEBUG ('s', "Get string with size %d, initiated by user program.\n", size);
        int totalread = 0;
        int nbread = MAX_STRING_SIZE-1;
        bufferSystem[nbread-1] = '\0';
        while(nbread >= MAX_STRING_SIZE-1 && bufferSystem[nbread-1] != '\n')
        {
          int remain = (size - totalread);
          int sizeBuffer = remain > MAX_STRING_SIZE ? MAX_STRING_SIZE : remain;

          DEBUG('s', "Size buffer system used : %d\n", sizeBuffer);
          synchconsole->SynchGetString(bufferSystem, sizeBuffer);
          DEBUG ('s',"Buffer content <%s>\n", bufferSystem);
          nbread = copyStringToMachine(bufferSystem, addr+totalread, sizeBuffer);
          DEBUG ('s', "%d character read.\n", nbread);
          totalread += nbread;
        }
        DEBUG ('s', "%d character read total.\n", totalread);
        accessBuffer->V();
        break;
      }

      case SC_ThreadCreate:
        {

          int addr_f = (int) machine->ReadRegister (4);
          int addr_arg = (int) machine->ReadRegister (5);

          int result = do_ThreadCreate(addr_f, addr_arg);
          DEBUG ('x', "Create new thread with result %d.\n", result);

          machine->WriteRegister(2, result);

          break;
        }

        case SC_ThreadExit:
          {
            DEBUG ('x', "Exit thread.\n");
            do_ThreadExit();
            break;
          }

      #endif // CHANGED

		default:
		  {
		    printf("Unimplemented system call %d\n", type);
		    ASSERT(FALSE);
		  }
	      }

	    // Do not forget to increment the pc before returning!
	    UpdatePC ();
	    break;
	  }

	case PageFaultException:
	  if (!type) {
	    printf("NULL dereference at PC %x!\n", machine->registers[PCReg]);
	    ASSERT (FALSE);
	  } else {
	    printf ("Page Fault at address %x at PC %x\n", type, machine->registers[PCReg]);
	    ASSERT (FALSE);	// For now
	  }
	  break;

	default:
	  printf ("Unexpected user mode exception %d %d at PC %x\n", which, type, machine->registers[PCReg]);
	  ASSERT (FALSE);
      }
}
