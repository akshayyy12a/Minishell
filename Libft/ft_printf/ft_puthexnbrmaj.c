/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexnbrmaj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:03:16 by mlouron           #+#    #+#             */
/*   Updated: 2025/05/20 12:01:31 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hexmajbase(int nb, size_t *count)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	write(1, &hex[nb], 1);
	(*count)++;
}

void	ft_puthexnbrmaj(unsigned int n, size_t *count)
{
	long	nb;

	nb = n;
	if (nb >= 16)
		ft_puthexnbrmaj(nb / 16, count);
	ft_hexmajbase(nb % 16, count);
}
