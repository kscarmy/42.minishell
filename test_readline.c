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

#include <readline/readline.h> // readline
#include <readline/history.h> // readline


#define TEST1 ".test1"
#define TEST2 ".test2"
#define TEST3 ".test3"
#define TEST4 ".test4"





int	main(void)
{
	char *tmp;
	int i = 0;


	while (i < 5)
	{
	tmp = readline("Jean : ");
	add_history(tmp);
	printf("'%s'\n", tmp);
	free(tmp);
	i++;
	}


	return (0);
}
