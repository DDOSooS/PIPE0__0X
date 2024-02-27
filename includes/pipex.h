/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:56:14 by aghergho          #+#    #+#             */
/*   Updated: 2024/02/27 20:34:55 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
#include "../ft_printf/ft_printf.h"

typedef struct cmds
{
    char        *cmd;
    int         in_flag;
    struct cmds *next;
}       t_cmd;

int     ft_strlen(char *str);
int     ft_strncmp(char *s1, char *s2, int n);
char    *ft_strdup(char *str);
void    ft_putstr_fd(char *str, int fd);
void	ft_free_mem(char **str);
char	**ft_split(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);

void    ft_pipex(t_cmd *cmds, char **env, int fd_input, int fd_out);
t_cmd	*ft_gen_cmds(int ac, char **av);
void	ft_free_cmds(t_cmd *head);
void	ft_42dup(int fd_in, int fd_out, int fd1, int fd2);
char    *ft_get_cmd_path(char *cmd, char **env);
int     ft_input_error(char *cmd, char *file);
int	    ft_handle_herdoc_input(char *delimiter ,int fd);
void    ft_error(int n);
void    ft_42close(int *fd);

# define BUFFER_SIZE 50

char	*get_next_line(int fd);
int		check_end_line(char *str);
char	*str_sub(char *str, int len);

#endif