/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 23:06:49 by aghergho          #+#    #+#             */
/*   Updated: 2024/03/01 23:06:52 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_cmd	*ft_new_node(char *str)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(str);
	if (!new->cmd)
	{
		free(new);
		return (NULL);
	}
	new->in_flag = 0;
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
	t_cmd	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->cmd);
		free(tmp);
	}
}

t_cmd	*ft_gen_cmds(int ac, char **av, int start)
{
	t_cmd	*cmd;
	t_cmd	*new;

	cmd = NULL;
	while (start < ac - 1)
	{
		new = ft_new_node(av[start]);
		if (!new)
		{
			ft_free_cmds(cmd);
			return (NULL);
		}
		ft_add_back(&cmd, new);
		start++;
	}
	return (cmd);
}

void	ft_error(int n, char *error)
{
	if (n == 10)
		ft_putstr_fd(error, 2);
	else if (n == 11)
		ft_putstr_fd(error, 2);
	else if (n == 12)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
	}
}
