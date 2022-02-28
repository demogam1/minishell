/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacey <pacey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:16:08 by pjacob            #+#    #+#             */
/*   Updated: 2021/10/15 11:44:26 by pacey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

char	*ft_strcpy(char *cpy, char *src)
{
	int		i;

	i = -1;
	if (!cpy)
		return (NULL);
	while (src[++i])
		cpy[i] = src[i];
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_realloc_char(char *src, char c)
{
	char	*new_str;
	int		i;

	i = -1;
	if (!src)
	{
		new_str = malloc(sizeof(char) * 2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
	}
	else
	{
		new_str = malloc(sizeof(char) * ft_strlen(src) + 2);
		if (!new_str)
			return (NULL);
		while (src[++i])
			new_str[i] = src[i];
		new_str[i++] = c;
		new_str[i] = '\0';
		free(src);
	}
	return (new_str);
}

void	*ft_calloc(int size, int type)
{
	char	*str;
	int		total;

	total = size * type;
	str = malloc(total);
	if (!str)
		return (NULL);
	ft_memset(str, 0, total);
	return ((void *)str);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
