/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:56:14 by aghergho          #+#    #+#             */
/*   Updated: 2024/02/19 17:08:51 by ddos             ###   ########.fr       */
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

typedef struct cmds
{
    char        *cmd;
    struct cmds *next;
}       t_cmd;

typedef struct pipes
{
    t_cmd           *cmds;
    int             fd_input;
    int             fd_output;
    struct pipes   *next;
}   t_pipe;


int     ft_strlen(char *str);
int     ft_strncmp(char *s1, char *s2, int n);
void    ft_putstr(char *str);
void    ft_putstr_fd(char *str, int fd);

char	**ft_split(char *str, char c);
void	ft_free_mem(char **str);
char	*ft_strjoin(char *s1, char *s2);

// int		ft_pipex_init(int ac, char **av);
// void	ft_pipex(t_cmd *head, char **env, int fd_out);
void    ft_pipex(t_cmd *cmds, char **env, int fd_input, int fd_out);
void	ft_error_handler(int i);
char    *ft_get_cmd_path(char *cmd, char **env);

# define BUFFER_SIZE 50

char	*get_next_line(int fd);
int		check_end_line(char *str);
char	*str_sub(char *str, int len);

#endif