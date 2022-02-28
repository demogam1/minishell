/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochichep <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:12:10 by ochichep          #+#    #+#             */
/*   Updated: 2021/04/08 15:07:55 by ochichep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nbr_strings(char const *s1, char c)
{
	int	nbr;
	int	cles;

	nbr = 0;
	cles = 0;
	if (*s1 == '\0')
		return (0);
	while (*s1 != '\0')
	{
		if (*s1 == c)
			cles = 0;
		else if (cles == 0)
		{
			cles = 1;
			nbr++;
		}
		s1++;
	}
	return (nbr);
}

static int	ft_strlen_char(char const *s2, char c, int i)
{
	int	len;

	len = 0;
	while (s2[i] != c && s2[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	**ft_copy_strings(char const *s, char **dst, char c, int total)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < total)
	{
		k = 0;
		while (s[i] == c)
			i++;
		dst[j] = (char *)malloc(sizeof(char) * ft_strlen_char(s, c, i) + 1);
		if (!dst[j])
			return (NULL);
		while (s[i] != '\0' && s[i] != c)
			dst[j][k++] = s[i++];
		dst[j][k] = '\0';
		j++;
	}
	dst[j] = 0;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		total;

	if (!s)
		return (NULL);
	total = nbr_strings(s, c);
	dst = (char **)malloc(sizeof(char *) * (total + 1));
	if (!dst)
		return (NULL);
	return (ft_copy_strings(s, dst, c, total));
}
