#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
	int maxpid;
	if ((maxpid = get_max_pid()) < 0) {
		printf(2, "get_max_pid error\n");
		exit();
	}
	printf(1, "Maximum PID: %d\n", maxpid);
	exit();
}
