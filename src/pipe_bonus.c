/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:18:54 by ddos              #+#    #+#             */
/*   Updated: 2024/02/26 10:25:29 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_handle_herdoc_input(int fd)
{
	char	*line;
	
	line = get_next_line(STDIN_FILNO);
	while (line)
	{
		if (write(fd, line, ft_strlen(line)) == -1)
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(STDIN_FILNO);
	}
	free(line);
	return (1);
}

int ft_handle_stand_input(char *io_file, int flag)
{
    int     io_fd;

    if (flag)
    {
		io_fd = open(".tmp" , "O_RWONLY" | O_CREATE , "0644");
		if (io_fd == -1)
			return (0);
		if(! ft_handle_herdoc_input(io_fd))
			return (0);
		dup2(io_fd, STDIN_FILNO);
		close(io_fd);
		unlink(".tmp");
    }
    else
    {
        io_fd = open(io_file, "O_RDONLY");
        dup2(io_fd, STDIN_FILNO);
		close(io_fd);  
    }
    return (1);
}

void    ft_pipex_bonus(t_cmd *cmds, char **envp, int fd_output)
{
    int	fd[2];
	int pid;

	if ()
}

int main(int ac, char **av, char **envp)
{
    int fd_input;
    int fd_output;
    t_cmd   *cmds;
    
    if (ac < 5)
        return ft_error_handler(1);
    cmds = ft_gen_cmds(av);
    if (! cmds)
        return (0)
    if (!ft_strncmp(av[1], "here_doc", 8))
    {
        if (! ft_handle_stand_input(av[2], 1))
            return 0;
    }
    else
        ft_handle_stand_input(av[1], 0);
    fd_output = open(av[ac - 1] , O_WRONLY, 0644);
    ft_pipex_bonus(cmds, envp, fd_output);
    ft_free_cmds(cmds);
    return (0);
}