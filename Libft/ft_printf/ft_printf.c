/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:27:09 by chevrethis        #+#    #+#             */
/*   Updated: 2025/05/20 12:16:29 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_va(char *str, va_list p, size_t *count)
{
	if (*str == 'c')
		ft_putchar(va_arg(p, int), count);
	else if (*str == 's')
		ft_putstr(va_arg(p, char *), count);
	else if (*str == 'p')
		ft_putpointer(va_arg(p, void *), count);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr(va_arg(p, int), count);
	else if (*str == 'u')
		ft_putposnbr(va_arg(p, unsigned int), count);
	else if (*str == 'x')
		ft_puthexnbr(va_arg(p, int), count);
	else if (*str == 'X')
		ft_puthexnbrmaj(va_arg(p, int), count);
	else if (*str == '%')
		ft_putchar(*str, count);
}

int	ft_printf(const char *str, ...)
{
	size_t	count;
	va_list	p;

	if (!str)
		return (0);
	va_start(p, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			print_va((char *)str, p, &count);
		}
		else
		{
			ft_putchar(*str, &count);
		}
		str++;
	}
	va_end(p);
	return (count);
}

// int	main(void)
// {
// 	int	*b;
// 	b = NULL;
// 	printf(" %d ", 	printf(" %p ", &b));
// 	printf(" %d ", 	ft_printf(" %p ", &b));
// }
