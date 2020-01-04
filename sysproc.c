#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


int sys_yield(void)
{
  yield(); 
  return 0;
}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// ********** CHANGED 1 START **********
int
sys_created_by_pmalloc(void){
  char* ptr;
  if(argptr(0, &ptr, 0))
    return -1;
  created_by_pmalloc((void*)ptr);
  return 0;
}

int
sys_set_pte_w_off(void){
  char* ptr;
  if(argptr(0, &ptr, 0))
    return -1;
  return set_pte_w_off((void*)ptr);
}

int
sys_turn_on_w(void){
  char* ptr;
  if(argptr(0, &ptr, 0))
    return -1;
  turn_on_w((void*)ptr);
  return 0;
}

int
sys_is_pte_w_on(void){
  char* ptr;
  char* ptr2;
  if(argptr(0, &ptr, 0))
    return -1;
  if(argptr(1, &ptr2, 0))
    return -1;
  return is_pte_w_on((void*)ptr, (int*)ptr2);
}
// ********** CHANGED 1 END **********
