#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_count_arg(char *str) 
{
    int counter = 0;
    int i = 0;

    while (str[i]) {
        while (str[i] && str[i] == ' ')
            i++;
        if (str[i]) 
            counter++;
        while (str[i] && str[i] != ' ')
            i++;
        
    }
    return counter;
}


int	ft_count_len(char *str)
{
	int   len;

    len = 0;
    while (str[len] && str[len] != ' ')
        len++;
    return (len);
}

void ft_free_mem(char **str)
{
	int    i;

    i = 0;
	while (str[i])
	{
        free(str[i]);
        i++;
    }
	free(str);
	// str = NULL;
}

// char *fr_gen_word(char *str, int len) {
//     char *word = (char *)malloc(sizeof(char) * (len + 1));

//     if (!word)
//         return NULL;

//     for (int i = 0; i < len; i++) {
//         word[i] = str[i];
//     }

//     word[len] = '\0';

//     return word;
// }

char *ft_gen_word(char *str,int len)
{
	char    *word;
    int        i;

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

int	ft_gen_words(char *str, char **words)
{
    int  i;
    int j;
    int len;

    i = 0;
    j = 0;
    while (str[i])
    {
        while (str[i] && str[i] ==' ')
            i++;
        if (str[i])
        {
            len = ft_count_len(&str[i]);
            words[j] = ft_gen_word(&str[i], len);
            j++;
            i += len;
        }

    }
    words[j] = NULL;
    return (1);
} 

char	**ft_gen_args(char *str)
{
	char	**args;
	int		n_args;

	n_args = ft_count_arg(str);
	args = (char **)malloc(sizeof(char *) * (n_args + 1));
	if (!args)
	    return (NULL);
	if (! ft_gen_words(str, args))
	{
		ft_free_mem(args);
        return (NULL);
	}
	return (args);
}


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char **args = ft_gen_args(argv[1]);

    if (!args) {
        fprintf(stderr, "Error generating arguments\n");
        return 1;
    }

    printf("\n=== %d args ===\n", argc);

    int i = 0;
    while (args[i]) {
        printf("======%s======\n", args[i]);
        i++;
    }

    ft_free_mem(args);

    return 0;
}
