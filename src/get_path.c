/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:30:25 by aghergho          #+#    #+#             */
/*   Updated: 2024/01/30 19:04:52 by aghergho         ###   ########.fr       */
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
        if (strncmp(env[i], "PATH=", 5) == 0)
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

char *ft_get_cmd_path(char *cmd, char **env)
{
    char    **paths;
    int     i;
    char    *cmd_path;
    
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

