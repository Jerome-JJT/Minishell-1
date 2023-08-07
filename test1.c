
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main()
{
 int	fd = open("/tmp/test", O_RDONLY);
	if (fd == -1) {
	 perror("open");
	}
}
