/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 09:50:59 by aghergho          #+#    #+#             */
/*   Updated: 2024/02/14 17:28:47 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/pipex.h"

int	ft_handle_proc(char *cmd, char **env)
{
	char	**args;
	char	*sh;

	args = ft_split(cmd, ' ');
	if (args == NULL)
		return (0);
	sh = ft_get_cmd_path(args[0], env);
	if (sh == NULL)
	{
		ft_free_mem(args);
		return (0);
	}
	if (execve(sh, args, env) == -1)
	{
		ft_free_mem(args);
		free(sh);
		perror("execve");
      return (0);
	}
	ft_free_mem(args);
	return (1);
}

void	ft_pipex(char *cmd, char **env)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return ft_putstr("pipe error\n");
	pid = fork();
	if (!pid)
	
		if(! ft_handle_proc(cmd, env))
			exit(0);	
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		return;
	}
}

int	ft_handle_fd_standard(int *fd_output, char **av, int ac)
{
	int	fd_inpnut;
	
	fd_inpnut = open(av[1], O_RDONLY);
	if (fd_inpnut == -1)
	{
		ft_putstr("----open error\n");
		return (0);
    }
	*fd_output = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT);
	if (*fd_output == -1)
	{
		ft_putstr("open error---\n");
		return (0);
	}
	dup2(fd_inpnut, STDIN_FILENO);
	return (1);
}

int	ft_handle_input(int *fd_output, char **av, int ac)
{
	int		tmp_fd;
	char	*line;

	tmp_fd = open(".tmp", O_CREAT | O_RDWR, 0644); 
	if (tmp_fd == -1)
		return (0);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, av[2], ft_strlen(av[2])) != 0)
	{
		write(tmp_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	*fd_output = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT);
	if (*fd_output == -1)
		return (0);
	close(tmp_fd);
	dup2(tmp_fd, STDIN_FILENO);
	unlink(".tmp");
	return (1);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	fd_output;

	
	i = -1;
	if (ac < 5)
	{
		ft_putstr("Usage:./pipex <input> <cmd ...> <output>\n");
		return (1);
	}
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		if (!ft_handle_input(&fd_output, av, ac))
			return (1);
	}
	else if (! ft_handle_fd_standard(&fd_output, av, ac))
		return (1);
	while (++i < ac - 4)
		ft_pipex(av[i + 2], env);
	dup2(fd_output, STDOUT_FILENO);
	ft_handle_proc(av[ac - 2], env);
	return (0);
}