/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:56:14 by aghergho          #+#    #+#             */
/*   Updated: 2024/01/31 11:32:39 by ddos             ###   ########.fr       */
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


int     ft_strlen(char *str);
int     ft_strncmp(char *s1, char *s2, int n);
void    ft_putstr(char *str);

char	**ft_split(char *str, char c);
void	ft_free_mem(char **str);
char	*ft_strjoin(char *s1, char *s2);

// int		ft_pipex_init(int ac, char **av);
void	ft_pipex(char *cmd, char **env);
void	ft_error_handler(int i);
char    *ft_get_cmd_path(char *cmd, char **env);

#endif