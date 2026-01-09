/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:03:23 by mlouron           #+#    #+#             */
/*   Updated: 2025/05/20 12:16:53 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putpointer(void *p, size_t *count)
{
	unsigned long	ptr;

	if (!p)
		return (ft_putstr("(nil)", count));
	ptr = (unsigned long)p;
	ft_putstr("0x", count);
	ft_puthexnbr_ulong(ptr, count);
}
