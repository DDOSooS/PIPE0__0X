/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:50:59 by aghergho          #+#    #+#             */
/*   Updated: 2024/01/24 19:54:29 by aghergho         ###   ########.fr       */
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

int pipex(int fd_input, int fd_output, char *av[])
{
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1)
        exit(1);
    pid = fork();
    if (pid == -1)
        exit(1);
    if (pid == 0)
    {
        close(fd[0]);
        ft_handle_proc(fd_input, fd[1], av[2]);
    }
    else
    {
        close(fd[1]);
        waitpid(pid, NULL, 0);
        ft_handle_proc(fd[0], fd_output, av[3]);
    }
	return 1;
}
// void pipex(int fd_input, int fd_output, char **av, int ac)
// {
//     int i;
//     int pid;
//     int fd[2];

//     i = 0;
//     while (i < ac - 3)
//     {
//         pid = fork();
//         if (pipe(fd) == -1)
//             return;
//         if (pid == 0 && !ft_handle_proc(fd_input, fd, av[i + 2]))
//             return;
//         else
//         {
//             close(fd[1]);
//             fd_input = fd[0];
//             if (i + 1 == ac - 3)
//             {
//                 fd[1] = fd_output;
//                 fd_input = fd[0]; // Update fd_input for the last command
//             }
//             i++;
//         }
//     }
// }

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
    pipex(fd_input, fd_output, av);
    close(fd_input);
    close(fd_output);
    return 0;
}

/*

int execute_cmd(int fd_input, int fd_output, char *arg)
{
    char **args;
    char *sh;
    
    dup2(fd_input, STDIN_FILENO);
    dup2(fd_output, STDOUT_FILENO);
    args = ft_pipex_parse_args(arg);
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

void ft_iterate_cmd(int fd_input, int fd_output, char **av, int ac)
{
    int i;
    int fd[2];
    int org_output;

    i = 0;
    org_output = fd_output;
    while (i < ac - 2)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            return;
        }
        if (i != 0)
            fd_input = fd[0];
        if (i == ac - 3)
            fd_output = org_output;
        else
            fd_output = fd[1];
        if (!execute_cmd(fd_input, fd_output, av[i + 1]))
        {
            printf("error\n");
            re
        i++;
    }turn;
        }
}

*/
// int main(int ac, char *av[])
// {
//     int fd_input, fd_output;

//     if (ac != 5)
//     {
//         ft_putstr("Usage:./pipex <input> <cmd1> <cmd2> <output>");
//         return 1;
//     }
//     fd_input = open(av[1], O_RDONLY);
//     fd_output = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
//     if (fd_input == -1 || fd_output == -1)
//     {
//         perror("open");
//         return 1;
//     }
//     ft_iterate_cmd(fd_input, fd_output, av, ac);
//     close(fd_input);
//     close(fd_output);
//     return 0;
// }























/*
int execute_cmd(int fd_input, int fd_output, char *arg)
{
    char **args;
    char *sh;
    
    dup2(fd_input, STDIN_FILENO);
    dup2(fd_output, STDOUT_FILENO);
    args = ft_pipex_parse_args(arg);
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

void ft_iterate_cmd(int fd_input, int fd_output, char **av, int ac)
{
    int i;
    int fd[2];
    int org_output;

    i = 0;
    org_output = fd_output;
    while (i < ac - 2)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            return;
        }
        if (i != 0)
            fd_input = fd[0];
        if (i == ac - 3)
            fd_output = org_output;
        else
            fd_output = fd[1];
        if (!execute_cmd(fd_input, fd_output, av[i + 1]))
        {
            printf("error\n");
            re
        i++;
    }turn;
        }
}

*/
// int main(int ac, char *av[])
// {
//     int fd_input, fd_output;

//     if (ac != 5)
//     {
//         ft_putstr("Usage:./pipex <input> <cmd1> <cmd2> <output>");
//         return 1;
//     }
//     fd_input = open(av[1], O_RDONLY);
//     fd_output = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
//     if (fd_input == -1 || fd_output == -1)
//     {
//         perror("open");
//         return 1;
//     }
//     ft_iterate_cmd(fd_input, fd_output, av, ac);
//     close(fd_input);
//     close(fd_output);
//     return 0;
// }

















/*
int execute_cmd(int fd_input, int fd_output, char *arg)
{
    char **args;
    char *sh;
    
    dup2(fd_input, STDIN_FILENO);
    dup2(fd_output, STDOUT_FILENO);
    args = ft_pipex_parse_args(arg);
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

void ft_iterate_cmd(int fd_input, int fd_output, char **av, int ac)
{
    int i;
    int fd[2];
    int org_output;

    i = 0;
    org_output = fd_output;
    while (i < ac - 2)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            return;
        }
        if (i != 0)
            fd_input = fd[0];
        if (i == ac - 3)
            fd_output = org_output;
        else
            fd_output = fd[1];
        if (!execute_cmd(fd_input, fd_output, av[i + 1]))
        {
            printf("error\n");
            re
        i++;
    }turn;
        }
}

*/
// int main(int ac, char *av[])
// {
//     int fd_input, fd_output;

//     if (ac != 5)
//     {
//         ft_putstr("Usage:./pipex <input> <cmd1> <cmd2> <output>");
//         return 1;
//     }
//     fd_input = open(av[1], O_RDONLY);
//     fd_output = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
//     if (fd_input == -1 || fd_output == -1)
//     {
//         perror("open");
//         return 1;
//     }
//     ft_iterate_cmd(fd_input, fd_output, av, ac);
//     close(fd_input);
//     close(fd_output);
//     return 0;
// }



















//=======================================================================================
/*
int execute_cmd(int fd_input, int fd_output, char *arg)
{
    char **args;
    char *sh;
    
    dup2(fd_input, STDIN_FILENO);
    dup2(fd_output, STDOUT_FILENO);
    args = ft_pipex_parse_args(arg);
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

void ft_iterate_cmd(int fd_input, int fd_output, char **av, int ac)
{
    int i;
    int fd[2];
    int org_output;

    i = 0;
    org_output = fd_output;
    while (i < ac - 2)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            return;
        }
        if (i != 0)
            fd_input = fd[0];
        if (i == ac - 3)
            fd_output = org_output;
        else
            fd_output = fd[1];
        if (!execute_cmd(fd_input, fd_output, av[i + 1]))
        {
            printf("error\n");
            re
        i++;
    }turn;
        }
}

*/
// int main(int ac, char *av[])
// {
//     int fd_input, fd_output;

//     if (ac != 5)
//     {
//         ft_putstr("Usage:./pipex <input> <cmd1> <cmd2> <output>");
//         return 1;
//     }
//     fd_input = open(av[1], O_RDONLY);
//     fd_output = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
//     if (fd_input == -1 || fd_output == -1)
//     {
//         perror("open");
//         return 1;
//     }
//     ft_iterate_cmd(fd_input, fd_output, av, ac);
//     close(fd_input);
//     close(fd_output);
//     return 0;
// }


