/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouron <mlouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:38:49 by chevrethis        #+#    #+#             */
/*   Updated: 2025/05/16 11:58:59 by mlouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Fonction pour compter le nombre de mots dans la chaîne

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

// Fonction pour allouer et copier un mot
static char	*allocate_word(char const *s, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_memcpy(word, s, len);
	word[len] = '\0';
	return (word);
}

// Fonction auxiliaire pour gérer l'allocation et l'incrémentation
static int	lilsplit(char **result, const char **s, char c, size_t *i)
{
	size_t	j;

	j = *i;
	result[*i] = allocate_word(*s, c);
	if (!result[*i])
	{
		while (j > 0)
			free(result[--j]);
		free(result);
		return (0);
	}
	(*i)++;
	while (**s && **s != c)
		(*s)++;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		words;
	char		**result;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!lilsplit(result, &s, c, &i))
				return (NULL);
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
