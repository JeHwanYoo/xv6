#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(void)
{
    if (hello() < 0) {
			printf(2, "hello error\n");
		}
    exit();
}
