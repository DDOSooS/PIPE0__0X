/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:05:05 by aghergho          #+#    #+#             */
/*   Updated: 2024/03/01 23:05:08 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_handle_stand_input(t_cmd *head, char *io_file, int flag)
{
	int	io_fd;

	if (flag)
	{
		io_fd = open(".tmp", O_RDWR | O_CREAT, 0644);
		if (io_fd == -1 || !ft_handle_herdoc_input(io_file, io_fd))
			return (0);
		close(io_fd);
		ft_reopen();
		unlink(".tmp");
	}
	else
	{
		io_fd = ft_open(io_file, 0);
		if (io_fd == -1)
		{
			head->in_flag = -1;
			return (ft_input_error(head->cmd, io_file));
		}
		dup2(io_fd, STDIN_FILENO);
		close(io_fd);
	}
	return (1);
}

int	ft_handle_output(int *fd, char *output)
{
	int	fd_out;

	if (fd && fd[0] != -1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else
	{
		fd_out = ft_open(output, 1);
		if (fd_out == -1)
			return (0);
		dup2(fd_out, STDOUT_FILENO);
	}
	return (1);
}

void	ft_execute_cmd(t_cmd *cmd, char **envp, int *fd, char *output)
{
	char	**args;
	char	*sh_cmd;

	if (cmd->in_flag && cmd->in_flag == -1)
		return ;
	if (!ft_handle_output(fd, output))
		return ;
	args = ft_split(cmd->cmd, ' ');
	if (!args)
		return (ft_error(10, "an error happen during execution"));
	sh_cmd = ft_get_cmd_path(args[0], envp);
	if (!sh_cmd)
		return (ft_free_mem(args));
	if (execve(sh_cmd, args, envp) == -1)
	{
		ft_free_mem(args);
		ft_error(11, "an error happened during the cmds execution");
		return (exit(0));
	}
}

void	ft_pipex_bonus(t_cmd *cmds, char **envp, char *output)
{
	int	fd[2];
	int	pid;

	fd[0] = -1;
	if (cmds == NULL)
		exit(0);
	if (cmds->next)
		pipe(fd);
	pid = fork();
	if (!pid)
		ft_execute_cmd(cmds, envp, fd, output);
	else
	{
		pid = fork();
		if (!pid && cmds->next)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			ft_pipex_bonus(cmds->next, envp, output);
		}
		ft_42close(fd);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmds;
	int		bonus;

	bonus = 2;
	if (ac < 5)
	{
		ft_putstr_fd(";) try again :  ./pipex in_file cmd1 cmd2 out_file", 2);
		return (1);
	}
	if (! ft_strncmp(av[1], "here_doc", 8))
		bonus = 3;
	cmds = ft_gen_cmds(ac, av, bonus);
	if (!cmds)
		return (0);
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		if (!ft_handle_stand_input(cmds, av[2], 1))
			return (0);
	}
	else
		ft_handle_stand_input(cmds, av[1], 0);
	ft_pipex_bonus(cmds, envp, av[ac - 1]);
	ft_free_cmds(cmds);
	return (0);
}
