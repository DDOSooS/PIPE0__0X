/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:49:36 by aghergho          #+#    #+#             */
/*   Updated: 2024/01/22 14:55:34 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_handle_proc(int fd_input, int fd_output, char *av)
{
	char	**args;
	char	*sh;

	dup2(fd_input, STDIN_FILENO);
	dup2(fd_output, STDOUT_FILENO);
	args = ft_pipex_parse_args(av);
	if (!args)
	{
		ft_free_mem(args);
		return (1);
	}
	sh = ft_strjoin("/bin/", args[0]);
	if (!sh)
	{
		ft_free_mem(args);
		return (2);
	}
	execve(sh, args, NULL);
	perror("execve");
	ft_free_mem(args);
	free(sh);
	return (2);
}

void	pipex(int fd_input, int fd_output, char **av)
{
	int	fd[2];
	int	pid;

	pid = fork();
	if (pid == -1 || pipe(fd) == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		if (!ft_handle_proc(fd_input, fd[1], av[2]))
			exit(1);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
		if (!ft_handle_proc(fd[0], fd_output, av[3]))
			exit(1);
	}
}

int	ft_pipex_init(int ac, char **av)
{
	int	fd_input;
	int	fd_output;

	if (ac != 5)
	{
		ft_putstr("Usage:./pipex <input> <cmd1> <cmd2> <output>\n");
		return (1);
	}
	fd_input = open(av[1], O_RDONLY);
	fd_output = open(av[ac - 1], O_WRONLY);
	if (fd_input == -1 || fd_output == -1)
	{
		perror("open");
		return (1);
	}
	pipex(fd_input, fd_output, av);
	close(fd_input);
	close(fd_output);
	return (0);
}
