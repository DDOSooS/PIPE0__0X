#include "pipex.h"

int ft_strlen(char *str)
{
	int i = 0;

    while (str[i]!= '\0')
        i++;
    return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
	    return (NULL);
	while (s1[++i])
	    str[i] = s1[i];
	while (s2[++j])
	    str[i + j] = s2[j];
	str[i + j] = '\0';
	printf("strjoun=%s==\n\n",str);
	return (str);
}