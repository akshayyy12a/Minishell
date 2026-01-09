/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chevrethis <chevrethis@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:13:26 by chevrethis        #+#    #+#             */
/*   Updated: 2025/05/13 13:09:33 by chevrethis       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_size(int n)
{
	long long int	nb;
	int				i;

	nb = n;
	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*itoa;
	int				count;
	int				i;
	long long int	nb;

	i = 0;
	nb = n;
	count = count_size(n);
	itoa = (char *)malloc(sizeof(char) * (count + 1));
	if (!itoa)
		return (NULL);
	itoa[count] = '\0';
	if (nb < 0)
	{
		nb = -nb;
		itoa[0] = '-';
		i++;
	}
	while (count > i)
	{
		count--;
		itoa[count] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (itoa);
}
