#include "../includes/pipex.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void ft_putstr_fd(char *str, int fd)
{
    int i;

    i = -1;
    while (str[++i])
        ft_putchar_fd(str[i], fd);
}