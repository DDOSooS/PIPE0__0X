/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:56:14 by aghergho          #+#    #+#             */
/*   Updated: 2024/01/30 19:03:41 by aghergho         ###   ########.fr       */
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

char	**pipex_parse_args(char *str);
void	ft_free_mem(char **str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_pipex_init(int ac, char **av);
char	**ft_split(char *str, char c);
void	ft_error_handler(int i);
void	ft_putstr(char *str);
int		ft_count_len(char *str, char c);
void	ft_pipex(char *cmd, char **env);
char *ft_get_cmd_path(char *cmd, char **env);

#endif