#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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

// SYSTEM CALL
// prints "helloxv6"
int
sys_hello(void) {
	cprintf("helloxv6\n");
	return 0;
}

// SYSTEM CALL
// @param 0 { char * } name (string)
// @returns { int } success: 0, failure: -1
// prints your name
int
sys_hello_name(void) {
	char *name = 0;
	if (argstr(0, &name) < 0) {
		return -1;
	}
	cprintf("hello %s\n", name);
	return 0;
}

// SYSTEM CALL
// @param 0 { int* } num
// @returns { int } success: 0, failure: -1
// assigns the number of current processes to the first parameter
// this calls 'do_proccnt()' of proc.c
int
sys_get_num_proc(void) {
	int *num;
	if (argptr(0, (void *)&num, sizeof(int *)) < 0) {
		return -1;
	}
	*num = do_proccnt();
	return 0;
}

// SYSTEM CALL
// @param 0 { int } pid
// @param 1 { structure processInfo * } return_info
// @returns { int } success: 0, failure: -1
// searches for the ptable as the first parameter and assigns it to the second parameter processInfo structure.
// this calls 'do_procinfo()' of proc.c
int
sys_get_proc_info(void) {
	int pid;
	struct processInfo *info;
	if (argint(0, &pid) < 0) {
		return -1;
	}
	if (argptr(1, (void *)&info, sizeof(info)) < 0) {
		return -1;
	}
	if (do_procinfo(pid, info) < 0) {
		return -1;
	}
	return 0;
}

// SYSTEM CALL
// @param 0 { int* } return_pids (array)
// @returns { int } success: 0, failure: -1
// assigns the value of pids to the integer array
// this calls 'do_procpids()' of proc.c
int
sys_get_proc_pids(void) {
	int *pids;
	if (argptr(0, (void *)&pids, sizeof(int *)) < 0) {
		return -1;
	}
	do_procpids(pids);
	return 0;
}

// SYSTEM CALL
// @param 0 { int* } return_pid
// @returns { int } success: 0, failure: -1
// assigns the value of maxpid to the first parameter.
// this calls 'do_maxpid()' of proc.c
int
sys_get_max_pid(void) {
	int *pid;
	if (argptr(0, (void *)&pid, sizeof(int *)) < 0) {
		return -1;
	}
	if((*pid = do_maxpid()) < 0) {
		return -1;
	}
	return 0;
}

// SYSTEM CALL
// @param 0 { int } prio
// set the priority of the current process
// this calls 'do_set_priority()' of proc.c
int
sys_set_prio(void) {
	int prio;
	if (argint(0, &prio) < 0) {
		return -1;
	}
	do_set_prio(prio);
	return 0;
}

// SYSTEM CALL
// @returns { int } Priority of the current process
// get the priority of the current process
// this calls 'do_get_priority()' of proc.c
int
sys_get_prio(void) {
	return do_get_prio();
}
