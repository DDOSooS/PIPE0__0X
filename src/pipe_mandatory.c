/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:05:18 by aghergho          #+#    #+#             */
/*   Updated: 2024/03/01 23:05:21 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_42dup(int fd_in, int fd_out, int fd1, int fd2)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd1);
	close(fd2);
}

int	ft_handle_standard(t_cmd *cmd, int *fd, int fd1)
{
	if (cmd->next != NULL)
	{
		if (fd1 != -1)
			ft_42dup(fd1, fd[1], fd[0], fd1);
		else
		{
			ft_putstr_fd("No such file or directory\n", 2);
			return (0);
		}
	}
	else
	{
		if (fd1 != -1)
			ft_42dup(fd[0], fd1, fd[1], fd[0]);
		else
		{
			ft_putstr_fd("No such file or directory\n", 2);
			return (0);
		}
	}
	return (1);
}

void	ft_execute_cmd(t_cmd *cmd, char **env, int *fd, int fd1)
{
	char	*sh_path;
	char	**args;

	if (!ft_handle_standard(cmd, fd, fd1))
		return ;
	args = ft_split(cmd->cmd, ' ');
	if (!args)
		return (ft_free_mem(args));
	sh_path = ft_get_cmd_path(args[0], env);
	if (!sh_path || execve(sh_path, args, env) == -1)
	{
		free(sh_path);
		free(args);
		return ;
	}
	return ;
}

void	ft_pipex(t_cmd *cmds, char **env, int fd_input, int fd_out)
{
	int		fd[2];
	pid_t	pid;
	pid_t	pid2;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		ft_execute_cmd(cmds, env, fd, fd_input);
	}
	else
	{
		if (cmds->next != NULL)
		{
			pid2 = fork();
			if (!pid2)
				ft_execute_cmd(cmds->next, env, fd, fd_out);
		}
		close(fd[1]);
		close(fd[0]);
		wait(NULL);
		wait(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmds;
	int		fd_input;
	int		fd_out;

	if (ac < 5)
	{
		ft_putstr_fd("Usage:./pipex <input> <cmd1> <cmd2> <output>\n", 2);
		return (1);
	}
	cmds = ft_gen_cmds(ac, av, 2);
	if (!cmds)
		return (1);
	fd_input = ft_open(av[1], 0);
	fd_out = ft_open(av[ac -1], 1);
	ft_pipex(cmds, env, fd_input, fd_out);
	ft_free_cmds(cmds);
	return (0);
}
