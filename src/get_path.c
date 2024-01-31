/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:30:25 by aghergho          #+#    #+#             */
/*   Updated: 2024/01/31 14:06:03 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char    **ft_get_paths(char **env)
{
    char    **paths;
    int     i;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
        {
            paths = ft_split(env[i], ':');
            if (!paths)
                return (NULL);
            return (paths);
        }
        i++;
    }
    return (NULL);
}


char    *ft_check_cmd_path(char *cmd, char *env)
{
    char *full_path;
    char *tmp;
    
    tmp = ft_strjoin(env, "/");
    if (!tmp)
        return (NULL);
    full_path = ft_strjoin(tmp, cmd);
    if (! full_path)
    {
        free(tmp);
        return (NULL);
    }
    if (access(full_path, F_OK) == -1)
    {
        free(full_path);
        free(tmp);
        return (NULL);
    }
    free(tmp);
    return (full_path);
}

char    *ft_format_cmd(char *cmd)
{
    int	i;

	i = 0;
	while (cmd[i] && cmd[i] == '/')
		i++;
	return(&cmd[--i]);
}

char *ft_get_cmd_path(char *cmd, char **env)
{
    char    **paths;
    int     i;
    char    *cmd_path;
 
 
    cmd_path = ft_format_cmd(cmd);
    if (access(cmd_path,  F_OK) != -1)
        return (cmd_path);
    paths = ft_get_paths(env);
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        cmd_path = ft_check_cmd_path(cmd, paths[i]);
        if (cmd_path)
            return (cmd_path);
        i++;
    }
    return (NULL);
}

