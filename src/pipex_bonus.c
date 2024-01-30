/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:49:24 by aghergho          #+#    #+#             */
/*   Updated: 2024/01/30 17:16:51 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int	ft_handle_child_proc(int fd_input, int *fd,
// char **cmd, int index, int ac)
// {
// 	char	**args;
// 	char	*sh;

// 	args = pipex_parse_args(cmd[index]);
// 	if (! args)
// 		return (0);
// 	sh = ft_strjoin("/bin/", args[0]);
// 	if (index == ac)
// 		dup2(fd_input, STDIN_FILENO);
// 	else
// 		dup2(fd[0], STDIN_FILENO);
// 	dup2(fd[1],STDOUT_FILENO);
// 	if (!sh || execve(sh, args, NULL) == -1)
// 	{
// 		perror("execve");
// 		ft_free_mem(args);
// 		free(sh);
// 		return (0);
// 	}
// 	return (1);
// }

// int	ft_handle_p_proc(int fd_output,int *fd, char **cmd, int index)
// {
// 	char	**args;
// 	char	*sh;

// 	args = pipex_parse_args(cmd[index]);
// 	if (! args)
// 		return (0);
// 	sh = ft_strjoin("/bin/", args[0]);
// 	dup2(fd[0], STDIN_FILENO);
// 	dup2(fd_output, STDOUT_FILENO);
// 	if (!sh || execve(sh , args, NULL) == -1)
// 	{
// 		perror("execve");
// 		ft_free_mem(args);
// 		free(sh);
// 		return (0);
// 	}
// 	return (1);
// }

// void ft_iterate_cmd(int fd_input,int fd_output,int ac, char **av, int index)
// {
// 	int	pid;
// 	int	fd[2];

// 	if (pipe(fd) == -1)
// 		return ;
// 	pid = fork();
// 	dup2(fd_input, STDIN_FILENO);
// 	if (pid == 0 && index <= ac - 1)
// 	{
// 		ft_iterate_cmd(fd_input, fd_output, ac, av, index + 1);
// 		if(!ft_handle_child_proc(fd_input, fd, av,index, ac))
// 			return ft_error_handler(1);
// 	}
// 	else
// 	{
// 		waitpid(pid, NULL, 0);
// 		if (!ft_handle_p_proc(fd_output, fd, av, index))
// 			return ft_error_handler(3);
// 	}
// 	return ;
// }

// int	ft_pipex_bonus(int ac, char **av)
// {
// 	int	fd_input;
// 	int	fd_output;

//     if (ac < 4)
//     {
//         perror("invalid format for exuction
// try with this format :<input file> <...cmd...>  <output file>");
//         return 1;
//     }
//     fd_input = open(av[1], O_RDONLY);
//     fd_output = open(av[ac - 1], O_WRONLY);
//     if (fd_input == -1 || fd_output == -1)
//     {
//         perror("error opening file");
//         return 1;
//     }
//     ft_iterate_cmd(fd_input,fd_output, ac, av, 2);
//     return 0;
// }
//=====================================================================================
#include "../includes/pipex.h"

int execute_cmd(int fd_input, int fd_output, char *arg)
{
    char **args;
    char *sh;
    
    dup2(fd_input, STDIN_FILENO);
    dup2(fd_output, STDOUT_FILENO);
    args = pipex_parse_args(arg);
    if (! args)
        return (0);
    sh = ft_strjoin("/bin/", args[0]);
    if (!sh || execve(sh, args, NULL) == -1)
    {
        perror("execve");
        ft_free_mem(args);
        free(sh);
        return (0);
    }
    return (1);
}

void    ft_iterate_cmd(int fd_input, int fd_output, char **av, int ac)
{
    int     i;
    int     fd[2];
    int     org_output;

    i = 0;
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return ;
    }
    while (i <= ac - 3)
    {
        if (i != 0)
            fd_input == fd[0];
        if (i == ac - 3)
            fd_output == org_output;
        fd_output == org_output;
        if (! execute_cmd(fd_input, fd_output, av[i + 2]))
            return ;
        i++;
    }
    return ;
}

int main(int ac, char *av[], char *)
{
    int fd_input, fd_output;

    if (ac != 5)
    {
        ft_putstr("Usage:./pipex <input> <cmd1> <cmd2> <output>");
        return 1;
    }
    fd_input = open(av[1], O_RDONLY);
    fd_output = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_input == -1 || fd_output == -1)
    {
        perror("open");
        return 1;
    }
    ft_iterate_cmd(fd_input, fd_output, av, ac);
    close(fd_input);
    close(fd_output);
    return 0;
}