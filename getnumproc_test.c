#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
	int num;
	if ((num = get_num_proc()) < 0) {
		printf(2, "get_num_proc error\n");
		exit();
	} 
	printf(1, "Total Number of Active Proccess: %d\n", num);
	exit();
}
