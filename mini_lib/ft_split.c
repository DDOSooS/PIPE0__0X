/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:59:08 by aghergho          #+#    #+#             */
/*   Updated: 2024/02/05 15:52:24 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/pipex.h"

int	ft_count_arg(char *str, char c)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			counter++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (counter);
}

void	ft_free_mem(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_gen_word(char *str, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

int	ft_gen_words(char *str, char **words, char c)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			len = 0;
			while (str[i] && str[i] != c)
			{
				len++;
				i++;
			}
			words[j] = ft_gen_word(&str[i - len], len);
			j++;
		}
	}
	words[j] = NULL;
	return (1);
}

char	**ft_split(char *str, char c)
{
	char	**args;
	int		n_args;

	n_args = ft_count_arg(str, c);
	args = (char **)malloc(sizeof(char *) * (n_args + 1));
	if (!args)
		return (NULL);
	if (! ft_gen_words(str, args, c))
	{
		ft_free_mem(args);
		return (NULL);
	}
	return (args);
}
