/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putposnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:03:26 by mlouron           #+#    #+#             */
/*   Updated: 2025/05/20 10:34:05 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putposnbr(unsigned int n, size_t *count)
{
	unsigned long	nb;

	nb = n;
	if (nb > 9)
		ft_putnbr(nb / 10, count);
	ft_putchar(nb % 10 + '0', count);
}
