/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:19:11 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/02 18:00:15 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(char const *line, char c, int i)
{
	int	count;

	count = 0;
	while (line[i])
	{
		if (line[i] == 34 && line[i + 1])
		{
			i++;
			while (line[i] != 34 && line[i + 1])
			{
				i++;
			}
		}
		if (line[i] == 39 && line[i + 1])
		{
			i++;
			while (line[i] != 39 && line[i + 1])
				i++;
		}
		if (line[i] == c && line[i + 1])
			count++;
		i++;
	}
	return (count);
}

static int	index_pipes(char const *line, char c, int i)
{
	while (line[i])
	{
		if (line[i] == 34 && line[i + 1])
		{
			i++;
			while (line[i] != 34 && line[i + 1])
				i++;
		}
		if (line[i] == 39 && line[i + 1])
		{
			i++;
			while (line[i] != 39 && line[i + 1])
				i++;
		}
		if (line[i] == c && line[i + 1])
			return (i);
		i++;
	}
	return (i);
}

static char	**ft_copy_strings(char *s, char **dst, char c, int total)
{
	int	i;
	int	j;
	int	k;
	int	index;

	i = 0;
	j = 0;
	while (j < total)
	{
		k = 0;
		while (s[i] == ' ')
			i++;
		index = index_pipes(s, c, i);
		dst[j] = (char *)ft_calloc(((index - i) + 1), sizeof(char));
		if (!dst[j])
			return (NULL);
		while (i < index)
			dst[j][k++] = s[i++];
		dst[j][k] = '\0';
		j++;
		i++;
	}
	dst[j] = 0;
	return (dst);
}

char	**ft_split_pipe(char *s, char c)
{
	char	**dst;
	int		total;

	if (!s)
		return (NULL);
	total = count_pipes(s, c, 0) + 1;
	dst = (char **)ft_calloc((total + 1), sizeof(char *));
	if (!dst)
		return (NULL);
	return (ft_copy_strings(s, dst, c, total));
}
