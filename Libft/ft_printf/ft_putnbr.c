/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:03:19 by mlouron           #+#    #+#             */
/*   Updated: 2025/05/20 11:37:27 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, size_t *count)
{
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		ft_putchar('-', count);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr(nb / 10, count);
	ft_putchar(nb % 10 + '0', count);
}
