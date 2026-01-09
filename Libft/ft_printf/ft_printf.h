/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:05:55 by mlouron           #+#    #+#             */
/*   Updated: 2025/05/20 12:01:53 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
void	ft_putchar(int c, size_t *count);
void	ft_putnbr(int n, size_t *count);
void	ft_putstr(char *str, size_t *count);
void	ft_puthexnbrmaj(unsigned int n, size_t *count);
void	ft_puthexnbr(unsigned int n, size_t *count);
void	ft_puthexnbr_ulong(unsigned long n, size_t *count);
void	ft_putposnbr(unsigned int n, size_t *count);
void	ft_putpointer(void *p, size_t *count);

#endif
