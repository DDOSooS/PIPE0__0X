/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:22:04 by ddos              #+#    #+#             */
/*   Updated: 2024/02/15 18:22:59 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int ft_handle_standard(int fd_input, int fd_out)
{
    op
}

void ft_execut_cmd(t_cmd *cmd, char **env, char *fd_input, char *fd_out)
{
    char    *sh_path;
    char    **args;

    if (!ft_handle_standard(fd_input, fd_out))
        return ;
    sh_path = ft_get_cmd_path(cmd->cmd, env);
    if (!sh_path)
        return ;
    args = ft_get_args(cmd->cmd);
    if (!args)
    {
        free(sh_path);
        return ;
    }
    if(exeve(sh_path, args, env) == -1)
    {
        free(sh_path);
        free(args);
        return ;
    }
    ft_free_mem(args);
    free(sh_path);
    return ;
}

void ft_pipex(t_cmd *cmds, char **env, char *fd_input, char *fd_out)
{
    int     fd[2];
    pid_t   pid;
    int     status;

    pipe(fd);
    pid = fork();
    if (!pid)
        ft_execute_cmd(cmds->cmd, env, fd_input, fd[1]);
    else if (pid > 0)
    {
        close(fd[1]);
        ft_execute_cmd(cmds->next, env, fd[0], fd_out);
        close(fd[0]);
        waitpid(pid, &status, 0);
    }
    close(fd_out);
    close(fd_input);
}

int main(int ac, char *av)
{
    t_cmd   *cmds;
    
    if (ac < 5)
    {
        ft_putstr_fd("Usage:./pipex <input> <cmd1> <cmd2> <output>\n", 2);
        return (1);
    }
    cmds = ft_gen_cmds(ac, av);
    if (!cmds)
    {
        ft_putstr_fd("Error: malloc\n", 2);
        ft_free_cmds(cmds);
        return (1);
    }
    ft_pipex(cmds, env, av[1], av[ac - 1]);
    return (0);
}