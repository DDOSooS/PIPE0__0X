# include "bonus/pipex_bonus.h"



int ft_handle_child_proc(int fd_input,int *fd, char **cmd, int index, int ac)
{
    char    **args;
    char    *sh;

    args = ft_pipex_parse_args(cmd[index]);
    sh = ft_strjoin("/bin/", args[0]);
    if (index == ac)
        dup2(fd_input, STDIN_FILENO);
    else
        dup2(fd[0], STDIN_FILENO);
    dup2(fd[1],STDOUT_FILENO);
    if (args == NULL || execve(sh, args, NULL) == -1)
    {
        perror("execve");
        ft_free_mem(args);
        free(sh);
        return (0);
	}
    return (1);
}

int ft_handle_p_proc(int fd_output,int *fd, char **cmd, int index)
{
    char **args;
    char *sh;

    args = ft_pipex_parse_args(cmd[index]);
    sh = ft_strjoin("/bin/", args[0]);
    dup2(fd[0],STDIN_FILENO);
    dup2(fd_output,STDOUT_FILENO);
    if (!sh || !args || (sh, args, NULL) == -1)
    {
        perror("execve");
        ft_free_mem(args);
        free(sh);
        return (0);
    }
    return (1);
}
void ft_iterate_cmd(int fd_input,int fd_output,int ac, char **av, int index)
{
    int pid;
    int fd [2];

    if (pipe(fd) == -1)
        return (1);
    pid = fork();
    dup2(fd_input, STDIN_FILENO);
    if (pid == 0 && index <= ac - 1)
    {
        ft_iterate_cmd(fd_input, fd_output, ac, av, index + 1);
        if(!ft_handle_child_proc(fd_input, fd, av,index))
            return ft_error_handler(1);
    }
    else
    {
        waitpid(pid, NULL, 0);
        if (!ft_handle_p_proc(fd_output, fd, av, index))
            return ft_error_handler(3);
    }
    return  ;
}

int pipex_bonus(int ac, char **av)
{
    int fd_input;
    int fd_output;

    if (ac < 4)
    {
        perror("invalid format for exuction try with this format :<input file> <...cmd...>  <output file>");
        return 1;
    }
    fd_input = open(av[1], O_RDONLY);
    fd_output = open(av[ac - 1], O_WRONLY);
    if (fd_input == -1 || fd_output == -1)
    {
        perror("error opening file");
        return 1;
    }
    if (! ft_ft_iterate_cmd(fd_input,fd_output, ac, av, 2))
        return 1;
    return 0;
}