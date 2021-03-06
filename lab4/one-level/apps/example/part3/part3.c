#include "usertraps.h"
#include "misc.h"
#include "os/memory_constants.h"

void main (int argc, char *argv[])
{
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  int * mem_loc;  //memory location

  if (argc != 2) { 
    Printf("Usage: %s <handle_to_procs_completed_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  s_procs_completed = dstrtol(argv[1], NULL, 10);

  // Now print a message to show that everything worked
  Printf("part3 (%d): Testing valid but unallocated virtual address\n", getpid());
  Printf("part3 (%d): START!\n", getpid());


  // We signal the semaphore before the process is finished because this 
  // process will die
  // Signal the semaphore to tell the original process that we're done
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("part3 (%d): Bad semaphore s_procs_completed (%d)!\n", getpid(), s_procs_completed);
    Exit();
  }

  // memory location that will be a seg fault
  mem_loc = (MEM_MAX_VIRTUAL_ADDRESS + 1 - MEM_PAGESIZE) - 4;
  Printf("part3 (%d): Accessing Memory Location: %d (decimal)\n", getpid(), mem_loc);
  // actually access it
  Printf("part3 (%d): Accessing Memory Location: %d (decimal)\n", getpid(), *mem_loc);
  Printf("part3 (%d): DONE!\n", getpid());

}
