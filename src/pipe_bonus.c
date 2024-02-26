/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 09:18:54 by ddos              #+#    #+#             */
/*   Updated: 2024/02/26 19:40:48 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    ft_42close(int *fd)
{
    int status;

    status = 0;
    close(fd[0]);
    close(fd[1]);
    while (wait(NULL) != -1)
        status++;
}

void    ft_error(int n)
{
    if (n == 10)
        ft_putstr_fd("an error happen during execution", 2);
    else if (n == 11)
        ft_putstr_fd("an error happened during the cmds execution", 2);
}

int    ft_error_handler(int n)
{
    if(n == 1)
        ft_putstr_fd("error try again :  ./pipex in_file cmd1 cmd2 out_file", 2);
    return (1);
}

int	ft_handle_herdoc_input(int fd)
{
	char	*line;
	
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (write(fd, line, ft_strlen(line)) == -1)
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	return (1);
}

int ft_handle_stand_input(char *io_file, int flag)
{
    int     io_fd;

    if (flag)
    {
		io_fd = open(".tmp" , O_RDWR | O_CREAT , "0644");
		if (io_fd == -1)
			return (0);
		if(! ft_handle_herdoc_input(io_fd))
			return (0);
		dup2(io_fd, STDIN_FILENO);
		close(io_fd);
		unlink(".tmp");
    }
    else
    {
        io_fd = open(io_file, O_RDONLY);
        dup2(io_fd, STDIN_FILENO);
		close(io_fd);  
    }
    return (1);
}

void ft_handle_output(int *fd, int fd_output)
{
    if (fd[0])
    {
        close(fd[0]);
        ft_putstr_fd("fd => null", 2);
        close(fd[1]);
        dup2(fd_output, STDOUT_FILENO);
    }
    else
        dup2(fd[1], STDIN_FILENO);
}

void ft_execute_cmd(t_cmd *cmd, char **envp, int *fd, int fd_output)
{
    char    **args;
    char    *sh_cmd;

    ft_handle_output(fd, fd_output);
    args = ft_split(cmd->cmd, ' ');
    if (! args)
        return ft_error(10);
    sh_cmd = ft_get_cmd_path(args[0], envp);
    if (! sh_cmd)
        return ft_free_mem(args);
    if (execve(sh_cmd, args, envp) == -1)
    {
        ft_free_mem(args);
        free(sh_cmd);
        ft_error(11);
        return ;
    }
}

void    ft_pipex_bonus(t_cmd *cmds, char **envp, int fd_output)
{
    int	fd[2];
	int pid;

    if (cmds == NULL)
        exit(0);
	
    if (cmds->next)
        pipe(fd);
    pid = fork();
    if (!pid)
        ft_execute_cmd(cmds, envp, fd, fd_output);
    else
    {
        pid = fork();
        if (!pid && cmds->next)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]);
            ft_pipex_bonus(cmds->next,envp , fd_output);    
        }
        ft_42close(fd);        
    }
}

int main(int ac, char **av, char **envp)
{
    int     fd_output;
    t_cmd   *cmds;
    
    if (ac < 5)
        return ft_error_handler(1);
    cmds = ft_gen_cmds(ac, av);
    if (! cmds)
        return (0);
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