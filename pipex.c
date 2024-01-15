#include <stdio.h>
#include <fcntl.h>

/*
steps
	->check the number of args
	->check if the first file exist 
	-
*/

/*
	iterate each command and execute theme to the inpute file 
*/
int	ft_iterate_cmd(int fd_input, int fd_output, char **cmds)
{
	int	fd[2];
	int pid;

	fork();
	if (pipe(fd) == -1)
		return (1);
	if (pid == 0)
	{
		
	}
	return (0);
}

int main (int argc,char **argv)
{
	int fd_input;
	int fd_output;
	int err_flag;

	err_flag = 0;
	if (argc != 4)
	{
		perror("pleas try again! whith this format : <exe file> <input file> <cmd1> <cmd2> <output file>");
		exit(0);
	}
	fd_input = open(argv[1], O_RDONLY);
	fd_output = open(argv[argc],O_RDWR);
	if (fd_input == -1 || fd_output == -1 )
	{
		perror("ERROR while trying to open the input FILE");
		exit(0);
	}
	err_flag = (fd_input, fd_output, argv);
    return (1);
}