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




// void	ft_jean_mich(void *p)
// {

// 	char	*str = &*p;
// 	printf ("<%p>\n", p);
// 	printf("str 1 '%s'\n", str);
// 	str[0] = 'B';
// 	printf("str 2 '%s'\n", str);
// 	// exit(0);

// }


int	main(void)
{
	// pid_t	pid;
	// int g_return;
	// void	*p;
	// int fd;
	// int	jean;

	// jean = dup(1);
	// unlink(TEST1);

	// if (argc < 2)
	// 	return (1);
	// open(TEST1, O_CREAT, 00777);
	// fd = open(TEST1, O_RDWR);

	// printf("1 %s\n", argv[1]);
	// if (fd > 0)
	// {
	// 	dup2(fd, 1);
	// }
	// printf("2 %s\n", argv[1]);
	// close(fd);
	// dup2(jean, 1);
	// close(jean);
	// printf("3 %s\n", argv[1]);
	// printf ("pre '%s'\n", argv[1]);
	// printf ("<%p>\n", argv[1]);

	// int		status;
	// p = argv[1];
	// pid = fork();
	// if (pid == -1)
		// printf("ERREUR TEST FORK\n");
	// else if (pid == 0)
		// ft_jean_mich((void*)argv[1]);
		// waitpid(pid, &g_return, 0);
	// printf ("<%p>\n", argv[1]);
	// printf ("after '%s'\n", argv[1]);

	return (0);
}
