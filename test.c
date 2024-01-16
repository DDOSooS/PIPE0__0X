#include <unistd.h>
#include "pipex.h"

int ft_handle_proc(char *str)
{
	char	**args;
	char	**env;
    char	*cmd;
    // printf("====STR:%s===",str);
	args = pipex_parse_args(str);
	env = NULL;
	if (!args)
	{
		ft_free_mem(args);
		return (1);
	}
	int		i;

	i = 0;
	while (args[i])
	{
		printf("\n=====arg[%d]=%s======\n",i,args[i]);
		i++;
	}
    str = ft_strjoin("/bin/",args[0]);
	if (execve(str, args, NULL) == -1)
	{
        ft_free_mem(args);
        return (2);
    }
	return (0);
}

int	ft_iterate_cmd(int fd_input, int fd_output, char **cmds)
{
	int	fd[2];
	int pid;

	pid = fork();
	if (pipe(fd) == -1)
		return (1);
	if (pid == 0)
	{
		dup2(fd_input, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		printf("\n==========child proc=========\n");
		if (!ft_handle_proc(cmds[2]))
		    return (2);
	}
	else
	{
		wait(NULL);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd_output, STDOUT_FILENO);
		printf("\n==========parent proc=========\n");
		if (ft_handle_proc(cmds[3]))
			return (3);
	}
	return (0);
}

int ft_pipex(int argc,char **argv)
{
	int fd_input;
	int fd_output;
	int err_flag;

	err_flag = 0;
	printf ("%d",argc);
	if (argc != 5)
	{
		perror("pleas try again! whith this format : <exe file> <input file> <cmd1> <cmd2> <output file>");
		exit(0);
	}
	fd_input = open(argv[1], O_RDONLY);
	fd_output = open(argv[argc - 1],O_RDWR);
	// printf("\n====%s============\n",argv[argc - 1]);
	if (fd_input == -1 || fd_output == -1 )
	{
		perror("ERROR while trying to open the input FILE");
		exit(0);
	}
	err_flag= ft_iterate_cmd(fd_input, fd_output, argv);
	if (err_flag)
		perror("\n====== ERROR DURING EXECUTION=====\n");
	return (1);
}

int main(int argc,char **av)
{
        int fd = open(av[1], O_RDONLY);
        int fd2 = open(av[3], O_RDWR);
        dup2(fd, STDIN_FILENO);
        dup2(fd2, STDOUT_FILENO);
        char **args = pipex_parse_args(av[2]);
        int     i;

        printf("\n=0:==%s==\n",args[0]);  
   
        char *str= ft_strjoin("/bin/",args[0]);
        printf("===========%s===============",str);
        execve(str, args, NULL);
        printf("\n==========================");

	// return (ft_pipex(argc,av));
}