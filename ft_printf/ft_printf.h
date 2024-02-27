/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddos <ddos@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 09:18:45 by ddos              #+#    #+#             */
/*   Updated: 2024/02/27 17:20:01 by ddos             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
void	ft_put_nbr(int number, int *counter);
void	ft_put_unsigned_nbr(unsigned int number, int *counter);
void	ft_put_adresse(unsigned long ptr, int *counter);
void	ft_put_hex_nbr(unsigned int number, int flag, int *counter);
void	ft_putchar(char c, int *counter);
void	ft_putstr(const char *str, int *counter);

#endif