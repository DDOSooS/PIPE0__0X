/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:50:59 by aghergho          #+#    #+#             */
/*   Updated: 2024/01/24 23:45:31 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int ft_handle_proc(int fd_input, int fd_output, char *cmd)
{
    char **args;

    args = ft_pipex_parse_args(cmd);
    dup2(fd_input, STDIN_FILENO);
    dup2(fd_output, STDOUT_FILENO);
    char *full_path = "/bin/";
    char *full_cmd = ft_strjoin(full_path, args[0]);
    if (!full_cmd)
    {
        ft_free_mem(args);
        return 0;
    }
    if (execve(full_cmd, args, NULL) == -1)
    {
        perror("execve");
        ft_free_mem(args);
        free(full_cmd);
        return 0;
    }
    ft_free_mem(args);
    return 1;
}


int pipex(int fd_input, int fd_output, char **av, int ac)
{
    int i;
    int pid;
    int fd[2];

    i = 0;
    while (i < ac - 3)
    {
        pid = fork();
        if (pipe(fd) == -1)
            return 0;
        if (pid == 0 && !ft_handle_proc(fd_input, fd[1], av[i + 2]))
            return 0;
        else
        {
            close(fd[1]);
            fd_input = fd[0];
            if (i + 1 == ac - 3)
            {
                fd[1] = fd_output;
                fd_input = fd[0];
            }
            i++;
        }
    }
    return 1;
}

int main(int ac, char *av[])
{
    int fd_input;
    int fd_output;

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
    pipex(fd_input, fd_output, av, ac);
    close(fd_input);
    close(fd_output);
    return 0;
}