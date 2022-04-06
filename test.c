# include <unistd.h> // WRITE FORK
# include <stdio.h> // PRINTF
# include <stdlib.h> // MALLOC FREE EXIT
# include <dirent.h> // opendir() for "cd"

# include <sys/types.h> // WAITPID
# include <sys/wait.h> // WAITPID
#include <termios.h> // SIGNALS
#include <signal.h> // SIGNALS

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TEST1 ".test1"
#define TEST2 ".test2"
#define TEST3 ".test3"
#define TEST4 ".test4"





int	main(int argc, char **argv)
{
	int fd;
	int	jean;

	jean = dup(1);
	unlink(TEST1);

	if (argc < 2)
		return (1);
	open(TEST1, O_CREAT, 00777);
	fd = open(TEST1, O_RDWR);

	printf("1 %s\n", argv[1]);
	if (fd > 0)
	{
		dup2(fd, 1);
	}
	printf("2 %s\n", argv[1]);
	close(fd);
	dup2(jean, 1);
	close(jean);
	printf("3 %s\n", argv[1]);


	return (0);
}
