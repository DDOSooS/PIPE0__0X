#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"

int ft_handle_proc(char *str)
{
	char	**args;
	char	*cmd;

    args = pipex_parse_args(str);
    if (!args)
    {
        ft_free_mem(args);
        return 1;
    }
    cmd = ft_strjoin("/bin/", args[0]);
    if (!cmd || !execve(cmd, args, NULL) == -1)
    {
        perror("execve");
        ft_free_mem(args);
        free(sh);
        return 2;
	}
    return 2;
}

int ft_iterate_cmd(int fd_input, int fd_output, char **cmds)
{
    int fd[2];
    int pid;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        dup2(fd_input, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        if (!ft_handle_proc(cmds[2]))
            exit(EXIT_FAILURE);
    }
    else
    {
        if (waitpid(pid, NULL, 0) == -1)
        {
            perror("waitpid");
            return 1;
        }
        dup2(fd[0], STDIN_FILENO);
		dup2(fd_output, STDOUT_FILENO);
        if (ft_handle_proc(cmds[3]))
            return 3;
    }
    return 0;
}

int ft_pipex(int argc, char **argv)
{
    int fd_input, fd_output, err_flag;

    if (argc != 5)
    {
        perror("Please try again with the format: <exe file> <input file> <cmd1> <cmd2> <output file>");
        exit(EXIT_FAILURE);
    }      
    fd_input = open(argv[1], O_RDONLY);
    fd_output = open(argv[argc - 1], O_RDWR);
    if (fd_input == -1 || fd_output == -1)
    {
        perror("Error while trying to open the input file");
        exit(EXIT_FAILURE);
    }
    err_flag = ft_iterate_cmd(fd_input, fd_output, argv);
    if (err_flag)
    {
        perror("\n====== ERROR DURING EXECUTION ======\n");
        exit(EXIT_FAILURE);
    }
    return 1;
}
