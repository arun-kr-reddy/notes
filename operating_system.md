- [introduction](#introduction)
- [process abstraction](#process-abstraction)
- [process API](#process-api)
- [process execution](#process-execution)
- [process scheduling](#process-scheduling)
- [inter-process communication](#inter-process-communication)
- [virtual memory](#virtual-memory)
- [address translation](#address-translation)
- [paging](#paging)
- [demand paging](#demand-paging)
- [memory allocation algorithms](#memory-allocation-algorithms)
- [threads and concurrency](#threads-and-concurrency)
- [locks](#locks)
- [conditional variables](#conditional-variables)
- [semaphores](#semaphores)
- [concurrency bugs](#concurrency-bugs)
- [communication with I/O devices](#communication-with-io-devices)
- [files \& directories](#files--directories)
- [file system implementation](#file-system-implementation)
- [hard disk internals](#hard-disk-internals)

# links  <!-- omit from toc -->
- [[playlist] operating systems](https://www.cse.iitb.ac.in/~mythili/os/)
- [cond-var vs mutex](https://medium.com/@abhisheksagar_59776/mutex-vs-condition-variables-e0a15b2226a4)

# introduction
- **operating system:** middleware between user programs & system hardware
  - **CPU:** provides process abstraction (create & manage processes)  
    each process has illusion of having complete CPU (CPU virtualization)  
    timeshares CPU between processes  
    enables coordination between processes
  - **memory:** each process thinks it has entire (virtual) memory space for itself  
    abstracts details of actual placement in memory (virtual ⟷ physical)
  - **devices:** device driver (OS code) manage hardware devices  
    issues instructions to devices and responds to device interrupts  
    also manages persistent data organized as filesystem on disk
- **OS design goals:**
  - convenient abstraction of hardware resources
  - efficient usage of hardware
  - isolation between multiple processes
- OS started out as library (procedure call) then evolved to system call  
  **procedure call:** jump to another function defined elsewhere in the program  
  **system call:** OS code function call that runs at higher privilege level of CPU  
  sensitive operations (like hardware access) only allowed at higher privilege level

# process abstraction
- **CPU scheduler:** pick one of many active processes to execute on CPU
  - **policy:** which process to run next
  - **mechanism:** how to context-switch between processes
- **process constituents:**
  - **process ID (PID):** unique identifier
  - **memory image:** static (code & data), dynamic (stack & heap)
  - **CPU context:** registers like program counter, current operands, stack pointer
  - **file descriptors:** pointers to open files (like stdout) & devices
- **process creation:**
  - allocate memory and create memory image
    load code & data from executable and create runtime stack & heap
  - open basic files (`stdin`, `stdout`, `stderr`)
  - initialize CPU registers (PC pointing to first instruction)
- **process states:**  
  ![](./media/operating_systems/process_states.png)
  - **running:** currently executing on CPU
  - **ready:** waiting to be scheduled
  - **blocked:** suspended and not ready to run  
    waiting for some event like read from disk
  - **new:** being created, yet to run
  - **dead:** terminated
- **process control block:** information about each process stored in a PCB  
  OS mantains data structure (like linked list) of all active process's PCB  
  - process identifier
  - process state
  - pointer to related processes (parent, child)
  - CPU context of process (saved when process is suspended)
  - pointers to memory locations
  - pointers to open files

# process API
- **process API:** set of system calls provided by OS
- **portable operating system interface (POSIX) API:** standard set of system calls that compliant OS must implement  
  program language libraries usually hide the details of invoking system calls
- **process related system calls:** multiple variants with different arguments exist
  - **fork:** create new child process  
    `init` process ancestor of all processes
  - **exec:** make process execute a given executable
  - **exit:** terminate a process
  - **wait:** causes parent to block until child terminates
- **fork working:**
  - new process created by making a copy of parent's memory image
  - new process added to OS process list and scheduled
  - parent & child resume execution from the same point just after fork (with different return values)  
  - parent & child execute and modify memory data independently
  ```cpp
  int foo()
  {
      int ret = fork();  // "ret" is child process PID

      if (ret < 0)  // fork failed
      {
          printf("fork failed \n";)
      }
      else if (ret == 0)  // child process
      {
          printf("child process %d \n", getpid());
      }
      else  // parent process
      {
          printf("parent process %d of child %d \n", getpid(), ret);
      }
  }
  ```
- **process termination**
  - calling `exit()`, is automatically called at end of main
  - OS terminates misbehaving process
- **child process handling:**
  - terminated process exist as a zombie
  - zombie child cleaned up (reaped) when parent calls `wait()`  
    parent blocked until child terminates (non-blocking wait also exist)
  - if parent terminates before child then `init` process adopts then reaps orphans
- after fork parent & child will same code which is not very useful  
  **exec:** load another executable (after fork) into child's memory image & run it
- **example: shell working:** `init` process (created after hardware init) spawns a shell  
  shell reads command ⟶ forks child ⟶ execs command ⟶ waits until done ⟶ reads next command  
  shell can also manipulate child (like redirect output using `>`)

# process execution
- OS kernel doesn't trust user programs  
  separate kernel stack used in kernel mode
  interrupt descriptor table (IDT) has addresses of kernel functions to handle system calls & other events (set up at boot time)
- **trap instruction:** special instruction run when system call is made  
  also used to handle program fault (like illegal access) & (device) interrupts  
  moves CPU to higher privilege level, saves user context on kernel stack and jumps to OS function in IDT  
  before returning to user mode (after trap execution) OS checks if it must switch to different process (scheduling or program fault)
- **user context:** when going from user mode to kernel mode, saved on kernel stack by trap instruction  
**kernel context:** during context switch, saved on kernel stack by context switching code

# process scheduling
- **scheduler mechanism:** process context (PC & other CPU registers) stored on kernel stack before context switch
  - **non-preemptive (cooperative):** switch only if process blocked or terminated
  - **preemptive (non-cooperative):** switch even when process is ready to continue  
    hardware generates periodic timer interrupt (trap instruction)
- **scheduler policy goals:**
  - **maximize utilization:** fraction of time CPU is used
  - **minimize average turnaround time:** time from process arrival to completion
  - **minimize average response time:** time from process arrival to first scheduling
  - **fairness:** all processes treated equally
  - **minimize overhead:** run process long enough to amortize context switch cost (~1ms)
- **scheduler policies:**
  - **first come first serve (FCFS):** schedule in the order they arrived  
    high turnaround time when stuck behind long process (convoy effect)
  - **shortest job first (SJF):** schedule job with shortest execution time first  
    can still get stuck if long process already executing
  - **shortest remaining time first (SRTF):** schedule job closest to completion  
    preemptive version of SJF
  - **round robin (RR):** each job scheduled for fixed time slice  
    good for response time & fairness but bad for turnaround time
  - **multi level feedback queue (MLFQ):** multiple queues with different priorities  
    within same priority any algorithm like RR

# inter-process communication
- **inter-process communication (IPC):** mechanisms to share information between processes  
  processes don't share any memory with each other  
  data buffering taken care by OS
  - **shared memory:** read/write same region of memory  
    passing same key to `int shmget(key,size, shmflg)` system call
  - **signals:** sent to a process by OS or another process  
    some signals have fixed meaning (like `SIGSEV`)  
    every process has default signal handler code  
    some can be overriden to do other things
  - **sockets:** can be used for two processes on same (Unix sockets) or different machines (TCP/UDP sockets)  
    two processes open sockets and connect them to each other  
    messages written into one socket can be read from another  
  - **pipes:** one-way (half-duplex) communication  
    system call returns two file handles  
    data written in write handle can be read through read handle  
      - **regular pipes:** both file handles used in same process  
        after fork parent uses one end and child uses other end
      - **named pipes:** two endpoints in different processes
  - **message queue:** process can open mailbox at specific location  
    processes can send/receive messages from mailbox
- **blocking vs non-blocking communication:** some IPC actions can block (like reading from empty queue)  
  instead read/write system calls with return error code exist

# virtual memory
- multiple active processes timeshare CPU so their memory image must be in memory  
  ![](./media/operating_systems/actual_memory.png)
- **virtual address space:** every process assumes it has access to large contiguous memory (from address 0 to MAX)  
  hides complexity of multiple processes non-contiguously sharing memory  
  ![](./media/operating_systems/virtual_memory.png)
- **address translation:** process issues load/store to virtual address (VA) but memory hardware accesses physical address (PA)  
   translation (VA to PA) done by memory management unit (MMU) hardware using information from OS
- **paging:** divide virtual address space into fixed-size pages and physical memory into frames  
  to allocate memory a page mapped to free physical frame  
  page table maps (process) virtual page number to physical frame number
- **memory virtualization goals:**
  - **transparency:** user programs shouldn't be aware of the messy details
  - **efficiency:** minimize overhead & wastage in terms of memory space & access time
  - **isolation & protection:** user process shouldn't be able to access anything outside its address space
- `brk()` (set program break) or `sbrk()` (increment/decrement program break) to grow/shrink heap  
  `mmap()` get (anonymous) memory page from OS
- **OS address space:** OS code is part of the virtual address space of every process  
  page table maps OS VA to actual OS code PA

# address translation
- **address translation in simplified OS:** place entire memory image in one chunk (page)  
  OS tells MMU the base (start address) & bound (total process size) values  
  MMU calculates PA from VA and checks if address is beyond bound  
  OS updates base & bound on context switch  
  OS maintains free list of memory & where each process's space is allocated (in PCB)
  ```cpp
  PA = VA + base;
  assert(PA < VA + base + bound);
  ```
- **segmentation:** generalized base & bounds where each segment of memory image placed separately with multiple base & bound values stored in MMU  
  good for sparse address space but leads to external fragmentation between segments  
![](./media/operating_systems/segmentation.png)
- **internal fragmentation:** process allocated more memory than it needs, wasting the excess  
  **external fragmentation:** total free memory is enough but is fragmented into small non-contiguous blocks  
  ![](./media/operating_systems/fragmentation.png)

# paging
- **paging:** allocate memory in fixed size chunks (pages)  
  avoids external fragmentation  
  but internal fragmentation due to partially-filled pages
- **example: paging:** 64byte address space in 128byte physical memory with 16byte page size  
  ![](./media/operating_systems/paging.png)
- **page table:** stores mappings(in PCB) from virtual page number (VPN) to physical frame number (PFN)  
  MMU uses page table for address translation  
  OS updates page table upon context switch
- **page table entry (PTE):** other than PFN contains few other bits like
  - **valid bit:** is this page used by process?
  - **protection bits:** read/write permissions
  - **present bit:** is this page in main memory?
  - **dirty bit:** has this page been modified?
  - **accessed bit:** has this page been recently accessed?
- **address translation in hardware:** most significant bits of VA give the VPN  
  MMU only stores PA of page table start so needs to walk to get relevant PTE (& its PFN)  
  ![](./media/operating_systems/address_translation.png)
- **translation lookaside buffer (TLB):** cache of recent VA-PA mappings maintained  
  MMU first looks up TLB, if TLB miss then extra latency to walk page table
- **page tables in memory:** with 32bit VA & 4KB pages we have `2^32/2^12 = 2^20` entries  
  if PTE is 4 bytes then page table (per process) is 4MB  
  to reduce size of page tables:
  - larger pages, so fewer entries  
    but leads to fragmentation
  - page table itself split into smaller chunks
- **multilevel page tables:** page table is spread over many pages  
  page directory (outer page table) tracks the PFNs of the page table pages  
  depending on how large the page table is we may need more than 2 levels  
  in case of TLB miss need to walk all page table levels so very expensive  
![](./media/operating_systems/linear_vs_multilevel_pagetable.png)  
for address translation first few bits of VA to identify outer page table entry, next few bits to index next level of PTEs  
![](./media/operating_systems/multilevel_pagetable_address.png)

# demand paging
- **demand paging:** main memory not always enough to store all the pages of all active processes  
  OS uses a part of disk (swap space) to store pages that are not in active use  
  ![](./media/operating_systems/swap_space.png)
- **page fault:** if page not in main memory (present bit reset) MMU raises trap to OS since it cannot access the disk  
  OS fetches disk address of page and issues read to disk  
  but since disk fetch is slow OS context switches to another process  
  when process scheduled again instruction that caused page fault restarted
- **page replacement policies:** if no free page available (when servicing page fault) then OS must swap out existing page  
  to prevent this OS proactively swap out pages to keep list of free pages handy
  - **optimal:** replace page not needed for longest time in future  
    theoretical since cannot calculate when page is needed in future
  - **first in first out (FIFO):** replace page that was brought into memory earliest  
    but that may be a popular page  
    increasing num page frames results in increase in num page faults (Belady's anomaly)
  - **least recently/frequently used (LRU/LFU):** replace page that was least recently (or frequently) used in the past  
    works well due to locality of references  
    OS periodically looks at accessed bit in PTE (set by MMU) to estimate pages that are active/inactive
- **memory access process:**
  - process issues load to VA  
    check CPU cache first, for miss go to main memory
  - MMU looks up TLB for VA
    if TLB hit obtain & fetch PA and return to process (via CPU caches)
  - if TLB miss MMU walks page table and obtains PTE:
    - if PTE present bit set, access memory
    - if not present but valid, raise page fault
    - if invalid page access, trap to OS for illegal access

# memory allocation algorithms
- **variable-sized allocation:** given a memory block allocate various memory allocation requests  
  implemented as `malloc()` in C lib
  **headers:** every allocated chunk has header containing size (used later by `free`)  
  may contain magic number for additional integrity checking  
  ![](./media/operating_systems/headers.png)  
  **free list:** free space managed as linked list  
  pointer to next free chunk embedded within current free chunk  
  library/kernel tracks head of the list and allocates from head  
  free chunks split & coalesced to satisfy variable-sized requests (external fragmentation)  
  ![](./media/operating_systems/free_list.png)
- **free list coalescing:** for a free request allocator will check if free chunk of memory being returned sits next to another free chunk  
  if yes then merge them into a single larger free chunk  
  example: non-coalesced free list: suppose three allocations of 100 bytes are deallocated in the order: last, first, middle
- **buddy allocation:** allocate memory in size of power-of-2  
  two free adjacent/buddy chunks can be merged to form a bigger power-of-2 chunk  
  ![](./media/operating_systems/buddy_allocation.png)
- **variable-size allocation strategies:**
  - **first fit:** allocate first free chunk that is sufficient
  - **best fit:** allocate free chunk that is closest in size
  - **worst fit:** allocate free chunk that is farthest in size  
    so remaining chunk is bigger & more usable
- **fixed-size allocation:**
  - **page-sized allocations:** maintain list of free (linked) list pages
  - **slab allocator:** pre-allocate fixed-size blocks of memory (slabs) which is further divided into smaller chunks (objects)  
  only certain object-sized allocation within a cache (one or more slabs)  
  each cache made up of one or more pages  
  ![](./media/operating_systems/slab_allocator.png)

# threads and concurrency
- **thread:** lightweight process that runs concurrently within the same process  
  each thread has separate PC & stack but share same address space (code & heap)  
  ![](./media/operating_systems/single_vs_multi_threaded.png)
- **parent forks a child:** no shared memory so need IPC for communication and extra copies of code & data  
  **parent executes two threads:** parts of address space shared so global variables used for communication and smaller memory footprint
- **parallelism:** running multiple threads/processes in parallel over different CPU cores  
  **concurrency:** running multiple threads/processes at same time by interleaving their execution (even on single CPU core)  
  even without parallelism, thread concurrency ensures effective CPU use when one of the threads blocked
- **scheduling threads:** OS schedules threads that are ready to run independently (much like processes)  
  context of a thread (PC, registers) saved-into/restored from thread control block (TCB)  
  every PCB has one or more linked TCBs
- **kernel threads:** threads that are scheduled independently by kernel (like linux pthreads)  
  **user-level threads:** provided by some libraries  
  library multiplexes large number of user threads over smaller number of kernel threads  
  low overhead for switching since expensive context switch not required  
  but all user threads cannot run in parallel
- **example: thread creation:**
  ```cpp
  #include <assert.h>
  #include <pthread.h>
  #include <stdio.h>

  void *mythread(void *arg)
  {
      printf("%s\n", (char *)arg);  // "A" then "B"
      return NULL;
  }

  int main(int argc, char *argv[])
  {
      pthread_t p1, p2;
      int rc;

      printf("main: begin\n");
      rc = pthread_create(&p1, NULL, mythread, "A");
      assert(rc == 0);
      rc = pthread_create(&p2, NULL, mythread, "B");
      assert(rc == 0);

      // join waits for the threads to finish
      rc = pthread_join(p1, NULL);
      assert(rc == 0);
      rc = pthread_join(p2, NULL);
      assert(rc == 0);
      printf("main: end\n");

      return 0;
  }
  ```
- **race condition:** when multiple threads (or processes) try to change shared data at the same time leading to unpredictable output
  ```cpp
  counter = counter + 1;  // in common thread function

  // in assembly
  100 mov    0x8049a1c, %eax
  104 add    $0x1, %eax       ⟵ if interrupted wrong value read by other thread
  108 mov    %eax, 0x8049a1c
  ```
- **critical section:** code segment that accesses shared resources  
  **mutual exclusion:** ensure only one thread can access shared resource at a time  
  **atomicity:** critical section should execute like one uninterruptible instruction

# locks
- **lock:** a variable that is either available (no thread holds it) or acquired (one thread holds it, other threads waiting)  
  makes sure only one thread is executing critical section  
  implementing locks needs support from hardware & OS
- **lock implementation goals:**
  - mutual exclusion
  - **fairness:** all threads should eventually get the lock, no thread should starve
  - **low overhead:** acquiring, releasing & waiting for lock shouldn't consume too many resources
- **is disabling interrupts enough:** can be used to implement locks only on single processor systems  
  but disabling interrupt is privileged instruction so malicious programs can misuse it (like run forever)  
  on multiprocessor systems another thread on another core can enter critical section
- **example: lock implementation using flag variable:** spin on flag variable until it is reset (spinlock)  
  but now race condition has moved to lock acquisition code  
  if thread context switched after spin wait but before setting flag then both threads acquire lock
  ```cpp
  typedef struct _lock_t(int flag;) lock_t;

  void init(lock_t *mutex)
  {
      // 0: lock is available, 1: held
      mutex->flag = 0;
  }

  void lock(lock_t *mutex)
  {
      while (mutex->flag == 1)  // test flag
          ;                     // spin wait
      mutex->flag = 1;          // set it
  }

  void unlock(lock_t *mutex) { mutex->flag = 0; }
  ```
- **hardware atomic instructions:** very hard to ensure atomicity only in software  
  modern architectures provide hardware atomic instructions
  - **test-and-set:** update variable and return old value all in single hardware instruction
    ```cpp
    int test_and_set(int *old_ptr, int new)
    {
        int old = *old_ptr;
        *old_ptr = new_val;
        return old;
    }
    ```
    ```cpp
    while (test_and_set(&lock->flag, 1) == 1)
    ```
  - **compare-and-swap:** update variable only if equal to expected and return actual value all in single hardware instruction
    ```cpp
    int compare_and_swap(int *ptr, int expected, int new)
    {
        int actual = *ptr;
        if (actual == expected) *ptr = new_val;
        return actual;
    }
    ```
    ```cpp
    while (compare_and_swap(&lock->flag, 0, 1) == 1)
    ```
- **(sleeping) mutex:** contending thread put to sleep when it fails to acquire a lock instead of busy waiting
  ```cpp
  void lock()
  {
      while (test_and_set(&lock->flag, 1) == 1)
          yield()  // give up CPU
  }
  ```
- **spinlock vs mutex:** 
    - **userspace:** most lock implementations are (sleeping) mutex since CPU wasted by spinning contending threads
    - **OS:** uses spinlocks since OS is default software layer and has no other thread to yield to  
    OS must disable interrupts while lock is held since interrupt handler could request same lock leading to deadlock  
    OS must never perform any blocking operation (go to sleep) with a locked spinlock
- **coarse-grained locking:** one big lock for all shared data  
  example: one lock for any change in entire linked-list  
  **fine-grained locking:** separate locks for individual shared data  
  allows more parallelism but multiple locks may be harder to manage  
  example: individual locks for each linked-list element

# conditional variables
- another common requirement in multi-threaded applications is waiting & signaling  
  can accomplish using busy-wait but inefficient  
  example: thread T1 wants to continue only after T2 has finished some task
- **conditional variables:** is a queue that a thread can put itself into when waiting on some condition  
  another thread that makes the condition true can signal the conditional variable to wake up a waiting thread
  - **signal:** wake up one thread
  - **broadcast:** wake up all waiting threads
- **cond-var vs mutex:** cond-var used to block a thread based on custom condition but mutex based on only one condition (mutex already locked or not)  
  cond-var often needs a mutex to ensure safe access to shared data  
  `while` instead of `if` in consumer to avoid spurious wakeups like some other thread modifying data between signal generated & delivered
  ```cpp
  // data consumer
  lock(data->mutex);                   // to prevent data modification
  while (is_available(data) == false)
  {
      wait(data->cond_var, data->mutex);  // unlocks mutex and wait for signal
                                          // mutex locks (acquired) again on signal
  }
  process(data);        // before unlock since modifies data
  unlock(data->mutex);  // unlock data mutex

  // data producer
  lock(data->mutex);
  if (is_available(data) == false)
  {
      prepare(data);
      signal(data->cond_var);
  }  // no deadlock of unlock with wait since wait lock would be blocked
  unlock(data->mutex);  // unlock data mutex

  ```
- **example: producer/consumer problem:** producer thread(s) & consumer thread(s) sharing bounded-size buffer  
  ![](./media/operating_systems/producer_consumer.png)
  ```cpp
  cond_t full, empty;
  mutex_t mutex;

  void *producer(void *arg)
  {
      while (1)
      {
          lock(mutex);
          if (is_buffer_full())
          {
              wait(full, mutex);
          }
          buffer.push(data);
          signal(empty);
          unlock(mutex);
      }
  }

  void *consumer(void *arg)
  {
      while (1)
      {
          lock(mutex);
          while (is_buffer_empty())
          {
              wait(empty, mutex);
          }
          process(buffer.pop());
          signal(full);
          unlock(mutex);
      }
  }
  ```

# semaphores
- **semaphores:** variable with an underlying counter (not visible to user)  
  `post` (or `up`) increments and `wait` (or `down`) decrements counter  
  thread calling `wait` blocked if resulting value negative
- **binary semaphore:** semaphore with init value `1` acts as mutex
  ```cpp
  sem_t lock;
  init(&lock, 1);

  wait(&lock);  // refcount 0
                // any other thread calling wait blocked (refcount -1)

  // CRITICAL SECTION

  post(&lock);
  ```
- **mutex vs cond-var vs semaphore:** mutex for locking and conditional variable for synchronization  
  semaphore both locking & synchronization (but less granular than cond-var)
- **example: producer/consumer with semaphore:** for signalling one counting semaphore to track empty slots and another to track full slots  
  and mutex (or binary semaphore) for buffer  
  `lock` after `wait` to prevent thread sleeping with mutex (no locks held when sleeping)
  ```cpp
  sem_t full, empty, mutex;

  sem_init(&full, 0);     // starts with none full
  sem_init(&empty, MAX);  // starts with all empty
  sem_init(&mutex, 1);

  void *producer(void *arg)
  {
      while (1)
      {
          wait(full);  // increment full

          wait(mutex);  // lock(mutex)
          buffer.push(data);
          post(mutex);  // unlock(mutex)

          post(empty);  // decrement empty
      }
  }

  void *consumer(void *arg)
  {
      while (1)
      {
          wait(empty);

          wait(mutex);
          buffer.push(data);
          post(mutex);

          post(full);
      }
  }
  ```

# concurrency bugs
- **concurrency bugs:** non-deterministic so very hard to debug since they occur based on execution order of threads
  - **non-deadlock:** not blocking but incorrect results
    - **atomicity:** atomicity assumptions violated during execution of concurrent threads  
      fix: use locks for mutual exclusion
    - **order-violation bugs:** desired order of memory access is flipped (assume another thread already ran)  
      fix: use conditional variables
  - **deadlocks:** threads cannot execute any further and wait for each other  
    ![](./media/operating_systems/deadlock_dependency.png)  
    all four conditions must hold for deadlock to occur:
    - **mutual exclusion:** a thread claims exclusive control of a resource
    - **circular wait:** there exists a cycle in the resource dependency graph  
      fix **total ordering:** always acquire locks in certain fixed order (like address)
      ```cpp
      if (m1 > m2)
      {
          lock(m1);
          lock(m2);
      }
      else
      {
          lock(m2);
          lock(m1);
      }
      ```
    - **hold-and-wait:** thread holds a resource and is waiting for another  
      fix: **master lock:** acquire all locks at once by acquiring a master lock first
      ```cpp
      lock(master);  // begin lock acquisition

      lock(m1);
      lock(m2);
      // ...

      unlock(master);  // end
      ```
    - **no preemption:** thread cannot be made to give up its resource
- **detect & recover:** modern OS detect deadlocks and reboot system or kill deadlocked processes


[continue](https://www.youtube.com/watch?v=7F4qQOSJGDw&list=PLDW872573QAb4bj0URobvQTD41IV6gRkx&index=17&pp=iAQB)



# communication with I/O devices
- **port:** point of connection to the system, I/O devices connect to the CPU & memory via a bus to a port on the machine
- **simple device model:** block devices store a set of numbered blocks (disks), character devices produce/consume stream of bytes (keyboard), devices expose an interface of memory registers (like current status of device, command to execute, data to transfer), internals of device are usually hidden
- **OS registers read/write:**
  - **explicit I/O instructions:** privileged instructions used by OS to read & write to specific registers on device
  - **memory mapped I/O:** device makes registers appear like memory locations, OS simply reads/writes from memory (part of address space reserved for I/O devices), memory hardware routes accesses to these special memory addresses to devices
- **example: simple execution of I/O requests:** polling status to see if device ready, wastes CPU cycles, CPU explicitly copies data to/from device (programmed I/O)
  ```cpp
  while (STATUS == BUSY)
      ;                               // wait until device is not busy
  write data to DATA register;        // programmed I/O
  write command to COMMAND register;  // starts the device and executes the command
  while (STATUS == BUSY)
      ;                               // wait until device is done with your request
  ```
- **interrupt request (IRQ):** polling wastes CPU cycles, instead OS can put process to sleep and switch to another process, when I/O request completes device raises interrupt  
![](./media/operating_systems/interrupt_request.png)
- **interrupt handler:** interrupt switches process to kernel mode, interrupt descriptor table (IDT) stores pointers to interrupt handlers (interrupt service routines (ISR)), IRQ number identifies the interrupt handler to run for a device, interrupt handler acts upon device notification and unblocks the process waiting for I/O (if any) then starts next I/O request (if any pending), handling interrupts imposes kernel mode transition overheads (polling may be faster than interrupts if device is fast)
- **direct memory access (DMA):** cpu cycles wasted in copying data to/from device, instead special piece of hardware (DMA engine) copies from main memory to device, CPU gives DMA engine the memory location, size & destination of data, in case of read interrupt raised after DMA completes, in case of write disk starts writing after DMA completes  
![](./media/operating_systems/direct_memory_access.png)
- **device driver:** part of OS code that talks to specific device, gives commands and handles interrupts, most OS code abstracts the device details, example: file system code is written on top of a generic block device  
![](./media/operating_systems/device_driver.png)

# files & directories
- **file:** linear array of bytes, stored persistently, identified with filename (human readable) and a OS level identifier index node (inode) number, inode number is unique within a filesystem
- **directory:** contains other subdirectories and files along with their inode numbers, stored like a file whose contents are filename-to-inode mappings
- **directory tree:** files & directories arranged in a tree starting with root (/)  
![](./media/operating_systems/directory_tree.png)
- **file operations:**
  - **create:** `open()` system call with flag to create, returns a numbers called file descriptor (fd)
  - **open:** existing files must be opened before they can be read/written, also uses `open()` system call and returns fd, all further operations on files uses the fd
  - **closing:** `close()` system call closes the file
  - **read/write:** `read()`/`write()` system calls, reading/writing happens sequentially by default (successive read/write calls fetch from current offset), `lseek()` system call lets you seek to random offset, writes are buffered in memory temporarily so `fsync()` system call flushes all writes to disk
  - other operations: rename file delete (unlink) file, get statistics of a file
- **directory operations:** directory can also be accessed like files, operations like create, open, read & close
- **example: `ls` program:** `ls` program opens and reads all directory entries
  ```cpp
  int main(int argc, char *argv[])
  {
      DIR *dp = opendir(".");
      assert(dp != NULL);
      struct dirent *d;
      while ((d = readdir(dp)) != NULL)
      {
          printf("%lu %s\n", (unsigned long)d->d_ino, d->d_name);
      }
      closedir(dp);
      return 0;
  }
  ```
- **hard link:** creates another file that points to the same inode number and hence same underlying data, even if one file deleted the file data can be accessed through the other links, inode maintains a link count, file data deleted only when no further links to it, you can only unlink, OS decides when to delete, linking created using `ln` command
  ```sh
  # same data
  $ echo hello > file
  $ cat file
  hello
  $ ln file file2  # command
  $ cat file 2
  hello

  # same inode number
  $ ls -i file file2
  67158084 file
  67158084 file2

  # link count
  $ rm file
  removed 'file'
  $ cat file2
  hello
  ```
- **soft/symbolic link:** is a file that simply stores a pointer to another filename, if main file is deleted then the link points to invalid entry (dangling reference)
  ```sh
  $ ls -al
  drwxr-x--- 2 remzi remzi 29 May 3 19:10 ./
  drwxr-x--- 27 remzi remzi 4096 May 3 15:14 ../
  -rw-r----- 1 remzi remzi 6 May 3 19:10 file
  lrwxrwxrwx 1 remzi remzi 4 May 3 19:10 file2 ⟶ file  # soft linking,
                                                        # note small size of soft link

  # same data
  $ echo hello > file
  $ ln -s file file2  # command
  $ cat file2
  hello

  # no link count
  $ rm file
  $ cat file2
  cat: file2: no such file or directory
  ```
- **mounting a file system:** mounting a file system connects the files to a specific point in the directory tree, several devices & file systems are mounted on a typical machine, using `mount` command
  ```sh
  $ mount -t ext3 /dev/sda1 /home/users
  $ ls /home/users/
  a b
  ```
- **memory mapping a file:** alternate way of accessing a file instead of using fd & read/write syscalls, `mmap()` allocates a page in virtual address space of a process, when file is mmaped file data copied into one or more pages in memory, can be accessed like any other memory location in program
  - **anonymous page:** used to store program data
  - **file-backed page:** contains data of file, filename provided as arg to `mmap()`

# file system implementation
- **file system:** an organization of files & directories on disk, OS has one or more file systems, disk exposes set of blocks (usually 512 bytes), file system organizes files onto blocks, two main aspects of file systems are
  - data structures to organize data & metadata on disk
  - implementation of system calls like open, read, write using data structures
- **simple file system organization:**  
![](./media/operating_systems/file_system_organization.png)
  - **data blocks:** file data stored in one or more blocks
  - **inode:** stores metadata about every file
  - **inode blocks:** each block has one or more inodes
  - **bitmaps:** indicate which inodes/data blocks are free, `i` & `d` in picture
  - **superblock:** holds master plan of all other blocks, example: which are inodes, which are data blocks, `S` in picture
- **inode table:** inodes usually stored in array, inode number of a file is index into this array, inode stores file metadata (like permissions, last accessed time) & pointers (disk block numbers) of file data  
![](./media/operating_systems/inode_table.png)
- **inode structure:** file data not stored contiguously on disk, so need to track multiple block numbers of file, inode tracks disk block numbers using
  - **direct pointers:** numbers of first few blocks are stored in inode itself, enough for small files
  - **indirect block:** for larger files inode stores number of indirect blocks which has block numbers of file data
  - similarly double & triple indirect blocks (multi-level index)
- **file allocation table (FAT):** alternate way to track file blocks, FAT stores next block pointer for each block, each disk block has one entry with number of next file block (or null if last block), pointer to first block stored in inode, similar to a linked list
- **directory structure:** directory stores records mapping filename to inode number, this mapping can be done using algorithms like linked list or hash table or binary search tree, directory is a special type of file and has inode & data blocks (which store the file records)
- **free space management:** to track free blocks
  - **bitmap:** store one bit per data block to indicate if free or not
  - **free list:** super block stores pointer to first free block which inturn stores address of next free block
- **opening a file:** to have the inode readily available (in memory) for future operations (read/write) on file
  - pathname of file is traversed starting from root, inode of root is known
  - recursively do: fetch inode of parent directory  ⟶  read its data blocks  ⟶  get inode number of each child  ⟶  fetch inode of child, repeat till end of path
  - if new file: new inode & data blocks will have to be allocated using bitmap and directory entry updated
- **open file table:** set of data structures to track open files
  - **global open file table:** one entry for every file opened (even sockets & pipes), entry points to in-memory copy of inode
  - **per-process open file table:** array of files opened by process, fd number is index into this array, per-process table entry points to global open file table entry, every process has three files open by default: std in, std out & std err (fd 0, 1 & 2), `open()` system call creates entries in both tables and returns fd number
- **reading/writing a file:**
  - access in-memory inode via fd
  - find location of data block at current read/write offset
  - fetch data from disk and perform operation
  - writes may need to allocate new blocks from disk using bitmap of free blocks
  - update time of access & other metadata in inode
- **virtual file system (VFS):** file systems differ in implementations of data structures, hence linux supports VFS abstraction, VFS looks a file systems as objects (files, directories, inodes, superblock) and operations on these objects (like lookup filename in directory), system call logic is written on VFS objects, to develop a new file system simply implement functions on VFS objects and provide pointers to these functions to kernel, syscall implementation doesn't have to change with file system implementation details
- **disk buffer cache:** results of recently fetched disk blocks are cached, file system issues block read/write requests via buffer cache, served from cache if cache hit, else block fetched to cache and returned to file system, unified page cache: free pages allocated to both processes and disk buffer cache from common pool, writes are applied to cache block either
  - **synchronously (write-through):** cache writes to disk immediately
  - **asynchronously (write-back):** cache stores dirty block in memory and writes back after delay
- **disk buffer benefits:**
  - improved performance due to reduced disk I/O
  - single copy of block in memory, so no inconsistency across processes

# hard disk internals
- **hard disk internals:** a set of 512 byte blocks (sectors) that can be read/written atomically, one or more platters connected by a spindle spin at ~10K rpm, each plater has a disk head & arm attached to it, a platter is divided into multiple tracks and each track into 512 byte sectors  
![](./media/operating_systems/hard_disk_internals.png)
- **hard disk sector access:** seek to the correct track while waiting for disk to rotate, example: sector 30 to 11  
![](./media/operating_systems/hard_disk_sector_access.png)
- **time taken for I/O operation:** given high seek & rotational latency usually rate of sequential access is much higher than random access
  - seek time to get to right track (few ms)
  - rotational latency for disk to spin to correct sector (few ms)
  - data transfer time to read sector (few tens μs)
- **disk scheduling:** requests to disk are not served in FIFO, they are reordered with other pending requests in order to read blocks in sequence as far as possible (to minimize seek time & rotational delay), OS doesn't know internal geometry of disk so scheduling done mostly by disk controller
  - **shortest seek time first (SSTF):** access block that we can seek to fastest, problem: some requests that are far from current position or head may never get served (starvation), example: from 30 go to 21 before 2  
  ![](./media/operating_systems/shortest_seek_time_first.png)
  - **elevator/SCAN algorithm:** disk head does one sweep over tracks and serves requests that fall on the path
    - **elevator/SCAN:** sweep outer to inner then inner to outer
    - **circular-SCAN:** sweep only one direction and circle back to start again, sweeping back & forth favors middle tracks more
    - **freeze-SCAN:** freeze queue while scanning to avoid starving far away requests
  - **shortest positioning time first (SPTF):** considers both seek time & rotational latency, example: better to serve 8 before 16 even though seek time is higher but 16 incurs a much higher rotational latency  
  ![](./media/operating_systems/shortest_positioning_time_first.png)
- **error detection/correction:** bits stored on disk with some error detection/correction bits, correct random bit flips or detect corruption of data, disk controller or OS can handle some errors (blacklisting certain sectors), if errors cannot be masked user perceives hard disk failures
- **redundant array of inexpensive disks (RAID):** provide high reliability & performance by replicating across multiple disks