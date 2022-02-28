/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:02:13 by pacey             #+#    #+#             */
/*   Updated: 2021/10/21 11:57:27 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

	i = -1;
	copy = (char *)malloc(sizeof(*s) * ft_strlen(s) + 1);
	if (!copy)
		return (NULL);
	while (++i < ft_strlen(s))
		*(copy + i) = *(s + i);
	copy[i] = '\0';
	return (copy);
}

int	ft_is_ascii(char c)
{
	if (c > 0 && c < 127)
		return (1);
	return (0);
}

char	*ft_realloc(char *s1, char *s2)
{
	char	*s_realloc;
	int		i;
	int		j;

	j = -1;
	i = -1;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	if (!s1 && !s2)
		return (NULL);
	s_realloc = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s_realloc)
		return (NULL);
	while (s1[++i])
		s_realloc[i] = s1[i];
	free(s1);
	while (s2[++j])
		s_realloc[i + j] = s2[j];
	s_realloc[i + j] = '\0';
	return (s_realloc);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
