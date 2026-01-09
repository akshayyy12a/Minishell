/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:03:13 by mlouron           #+#    #+#             */
/*   Updated: 2025/05/20 12:01:36 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hexbase(int nb, size_t *count)
{
	char	*hex;

	hex = "0123456789abcdef";
	write(1, &hex[nb], 1);
	(*count)++;
}

void	ft_puthexnbr(unsigned int n, size_t *count)
{
	long	nb;

	nb = n;
	if (nb >= 16)
		ft_puthexnbr(nb / 16, count);
	ft_hexbase(nb % 16, count);
}

void	ft_puthexnbr_ulong(unsigned long n, size_t *count)
{
	if (n >= 16)
		ft_puthexnbr_ulong(n / 16, count);
	ft_hexbase(n % 16, count);
}
