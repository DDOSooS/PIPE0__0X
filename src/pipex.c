/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:50:59 by aghergho          #+#    #+#             */
/*   Updated: 2024/01/30 19:03:57 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_handle_proc(char *cmd, char **env)
{
	char	**args;
	char	*sh;
	
	args = ft_split(cmd, ' ');
	if (args == NULL)
	    return (0);
	sh = ft_get_cmd_path(cmd, env);
	if (sh == NULL)
	{
		ft_free_mem(args);
		return (0);
	}
	if (execve(sh, args, NULL) == -1)
	{
		perror("execve");
		ft_free_mem(args);
        return (0);
	}
	ft_free_mem(args);
	return (1);
}

void	ft_pipex(char *cmd, char **env)
{
	int fd[2];
	int pid;

	if (pipe(fd) == -1)
		return ft_putstr("pipe error\n");
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if(! ft_handle_proc(cmd, env))
		exit(0);	
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

int	ft_handle_fd_standard(int *fd_output, char **av, int ac)
{
	int	fd_inpnut;
	
	fd_inpnut = open(av[1], O_RDONLY);
	if (fd_inpnut == -1)
	{
        ft_putstr("open error\n");
        return (0);
    }
	*fd_output = open(av[ac - 1], O_WRONLY);
	if (*fd_output == -1)
	{
        ft_putstr("open error\n");
        return (0);
    }
	dup2(fd_inpnut, STDIN_FILENO);
	return (1);
}

int main(int ac, char **av, char **env)
{
	int i;
	int	fd_output;

	i = -1;
	if (ac < 5)
	{
		ft_putstr("Usage:./pipex <input> <cmd ...> <output>\n");
        return (1);
	}
	if (! ft_handle_fd_standard(&fd_output, av, ac))
		return (1);
	while (++i < ac - 4)
		ft_pipex(av[i + 2], env);
	dup2(fd_output, STDOUT_FILENO);
	ft_handle_proc(av[ac - 2], env);
	return (0);
}