#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char **argv)
{
	char *name = 0;

	if (argc < 2) {
		printf(1, "[Usage] %s {name}\n", argv[0]);		
		exit();
	}
	name = argv[1];
  if (hello_name(name) < 0) {
		printf(2, "hello_name error\n");
	}
  exit();
}
