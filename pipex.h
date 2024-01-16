#ifndef PIPEX_H
# define    PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

char	**pipex_parse_args(char *str);
void    ft_free_mem(char **str);
int     ft_pipex(int argc,char **argv);
char    *ft_strjoin(char *s1, char *s2);
#endif