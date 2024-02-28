/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:32:39 by ddos              #+#    #+#             */
/*   Updated: 2024/02/28 23:30:14 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void ft_42close(int *fd)
{
    int status;

    status = 0;
    close(fd[0]);
    close(fd[1]);
    while (wait(NULL) != -1)
        status++;
}

int ft_handle_herdoc_input(char *delimiter, int fd)
{
    char *line;
    int len;

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

int ft_input_error(char *cmd, char *file)
{
    char **args;

    args = ft_split(cmd, ' ');
    if (!args)
        return 0;
    ft_printf("%s: %s: No such file or directory\n", args[0], file);
    return 0;
}