/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:06:36 by aghergho          #+#    #+#             */
/*   Updated: 2024/03/01 23:06:39 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_reopen(void)
{
	int	fd;

	fd = open(".tmp", O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ft_42close(int *fd)
{
	int	status;

	status = 0;
	if (fd[0] != -1)
	{
		close(fd[0]);
		close(fd[1]);
	}
	while (wait(NULL) != -1)
		status++;
}

int	ft_handle_herdoc_input(char *delimiter, int fd)
{
	char	*line;
	int		len;

	len = ft_strlen(delimiter);
	ft_putstr_fd("pipe heredoc> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strncmp(line, delimiter, len) != 0)
	{
		if (write(fd, line, ft_strlen(line)) == -1)
		{
			free(line);
			return (0);
		}
		free(line);
		ft_putstr_fd("pipe heredoc> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	return (1);
}

int	ft_input_error(char *cmd, char *file)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		return (0);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	ft_free_mem(args);
	return (0);
}
