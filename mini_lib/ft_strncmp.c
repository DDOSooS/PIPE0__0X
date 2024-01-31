/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:09:38 by aghergho          #+#    #+#             */
/*   Updated: 2024/01/31 12:40:28 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, int n)
{
	int    i;

    i = 0;
    while (i < n - 1 && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}
// #include <stdio.h>
// int main ()
// {
//     int i=ft_strncmp("a", "a",5);
//     printf("%d--",i);   
//     return (0);
// }