/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:58:23 by ddos              #+#    #+#             */
/*   Updated: 2024/02/14 19:19:37 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/pipex.h"
# include <string.h>

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

int	ft_handle_proc(t_cmd *cmd, char **env)
{
	char	**args;
	char	*sh;

	args = ft_split(cmd->cmd, ' ');
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

void ft_pipex(t_cmd *head, char **env, int fd_out)
{
    int pid;
    int pid2;
    int fd[2];

    pipe(fd);
    pid = fork();
    if (pid == 0)
    {	
		close(fd[0]);
		if (head->next)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		ft_handle_proc(head, env);
		return ;
	}
	else
	{
        head = head->next;
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
        pid2 = fork();
        if (pid2 == 0 && head)
            ft_pipex(head, env, fd_out);
		else
		{
			close(fd[0]);
			close(fd[1]);
			return ;
		}
	}
}


int	ft_handle_input(char *input, char *output, int *fd_output)
{
	int	fd_input;

	fd_input = open(input, O_RDONLY, 0644);
	if (fd_input == -1)
		return (0);
	*fd_output = open(output, O_WRONLY | O_CREAT, 0644);
	if (*fd_output == -1)
	    return (0);
	return (1);
}
int	ft_handle_input_heredoc(int *fd_output, char **av, int ac)
{
	int		tmp_fd;
	char	*line;

	tmp_fd = open(".tmp", O_CREAT | O_RDWR, 0644); // 0644 is the file permission mode
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
	*fd_output = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (*fd_output == -1)
		return (0);
	close(tmp_fd);
	dup2(tmp_fd, STDIN_FILENO);
	unlink(".tmp");
	return (1);
}
int main(int ac, char **av, char **env)
{
    t_cmd	*args;
    int		fd_output;

    // if (ac < 5)
    // {
    //     printf("\ntry: ./pipex input cmd1 ... output\n");
    //     return (1);
    // }
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		if (!ft_handle_input_heredoc(&fd_output, av, ac))
			return (1);
	}
	else if (! ft_handle_input(av[1], av[ac - 1], &fd_output))
		return (1);
	args = ft_gen_cmds(ac - 1, av);
	if (! args)
	    return (1);
	ft_pipex(args, env, fd_output);
	printf("\ndoneeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");
	ft_free_cmds(args);
    return (0);
}