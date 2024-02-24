/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:22:04 by ddos              #+#    #+#             */
/*   Updated: 2024/02/19 20:56:06 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <string.h>

t_cmd	*ft_new_node(char *str)
{
	t_cmd    *new;

    new = (t_cmd *)malloc(sizeof(t_cmd));
    if (!new)
	    return (NULL);
	new->cmd = strdup(str);
	if (! new->cmd)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
    return (new);
}

void	ft_add_back(t_cmd **head, t_cmd *cmd)
{ 
	t_cmd	*tmp;
	
	if (!*head)
	{
    	*head = cmd;
		return ;
    }
	tmp = *head;
	while (tmp->next)
	    tmp = tmp->next;
	tmp->next = cmd;
	return ;
}

void	ft_free_cmds(t_cmd *head)
{
	t_cmd    *tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->cmd);
        free(tmp);
    }
}

t_cmd	*ft_gen_cmds(int ac, char **av)
{
	t_cmd	*cmd;
	int		i;
	t_cmd	*new;
	
	cmd = NULL;
    i = 2;
	while (i < ac - 1)
	{
		new = ft_new_node(av[i]);
		if (!new)
		{
			ft_free_cmds(cmd);
            return (NULL);
		}
		ft_add_back(&cmd, new);
		i++;
	};
    return (cmd);
}

void	ft_42dup(int fd_in, int fd_out, int fd1, int fd2)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd1);
	close(fd2);
}

int ft_handle_standard(t_cmd *cmd, int *fd, int fd1)
{
	if (cmd->next != NULL)
	{
		if (fd1 != -1)
			ft_42dup(fd1, fd[1], fd[0], fd1);
		else
			return (0);
	}
	else
	{
		if (fd1 != -1)
			ft_42dup(fd[0], fd1, fd[1], fd[0]);
		else
			return (0);
	}
	return (1);
}

void ft_execute_cmd(t_cmd *cmd, char **env,int *fd, int fd1)
{
    char    *sh_path;
    char    **args;

	if (! ft_handle_standard(cmd, fd, fd1))
		return ;
    args = ft_split(cmd->cmd, ' ');
    if (!args)
        return ft_free_mem(args);
    sh_path = ft_get_cmd_path(args[0], env);
	if(!sh_path || execve(sh_path, args, env) == -1)
    {
        free(sh_path);
        free(args);
        return ;
    }
    return ;
}

void ft_pipex(t_cmd *cmds, char **env, int fd_input, int fd_out)
{
    int fd[2];
    pid_t pid;
    pid_t pid2;
    
	pipe(fd);
	pid = fork();
	if (!pid)
		ft_execute_cmd(cmds, env, fd, fd_input);
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

char	ft_handle_input(char **av, int *fd_input)
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
	close(tmp_fd);
	return (1);
}




int main(int ac, char **av, char **env)
{
    t_cmd *cmds;
    int fd_input;
    int fd_out;
    
	if (ac < 5)
	{
		ft_putstr("Usage:./pipex <input> <cmd1> <cmd2> <output>\n");
		return 1;
	}
    cmds = ft_gen_cmds(ac, av);
    if (!cmds)
        return 1;
	if (ft_strncmp("here_doc", av[1], 6) == 0 &&  )	
	{
		

	}
    else
		fd_input = open(av[1], O_RDONLY);
    fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ft_pipex(cmds, env, fd_input, fd_out);
    ft_free_cmds(cmds);
    return 0;
}