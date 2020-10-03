#include "types.h"
#include "stat.h"
#include "processInfo.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
	struct processInfo info;
	int pids[100];
	int i;

	if (get_proc_pids(pids) < 0) {
		printf(2, "get_proc_pids error\n");
		exit();
	}

	printf(1, "PID        PPID       SIZE       Number of Context Switch\n");
	for (i = 0; pids[i] != -1; i++) {
		if (get_proc_info(pids[i], &info) < 0) {
			printf(2, "get_proc_info error\n");
			exit();
		}
		printf(1, "%d          %d          %d      %d\n", pids[i], info.ppid, info.psize, info.numberContextSwitches);
	}
	exit();
}
