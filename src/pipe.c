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
	while (i < ac)
	{
		new = ft_new_node(av[i]);
		if (!new)
		{
			ft_free_cmds(cmd);
            return (NULL);
		}
		ft_add_back(&cmd, new);
		i++;
	}
    return (cmd);
}

int ft_handle_standard(int fd_input, int fd_output)
{
    if(fd_input < 0 || fd_output < 0)
        return (0);
    dup2(fd_input, STDIN_FILENO);
    dup2(fd_output, STDOUT_FILENO);
	close(fd_input);
	close(fd_output);
    return (1);
}

void ft_execute_cmd(t_cmd *cmd, char **env)
{
    char    *sh_path;
    char    **args;

    // if (!ft_handle_standard(fd_input, fd_out))
    //     return ;
    // printf("\n===(%s)===\n",cmd->cmd);
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

void ft_pipex(t_cmd *cmds, char **env, int fd_input, int fd_out) {
    int fd[2];
    pid_t pid;

    pipe(fd);
    pid = fork();
	if (pid == 0)
	{
        close(fd[0]);
        ft_handle_standard(fd_input, fd[1]);
        ft_execute_cmd(cmds, env);
    }
	else
	{
        close(fd[1]);
        ft_handle_standard(fd[0], fd_out);
        pid = fork();
   		if (pid == 0)
            ft_execute_cmd(cmds->next, env);
        else
		{
            wait(NULL); 
            wait(NULL);
            close(fd_out);
            close(fd[0]);
			close(fd[1]);
        }
    }
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
	{
        ft_putstr("Error: malloc\n");
        return 1;
    }
    fd_input = open(av[1], O_RDONLY);
    fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    ft_pipex(cmds, env, fd_input, fd_out);
    close(fd_input);
    close(fd_out);
    ft_free_cmds(cmds);
    return 0;
}