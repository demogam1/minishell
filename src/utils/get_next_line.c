/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:35:33 by haroun            #+#    #+#             */
/*   Updated: 2021/11/02 11:41:18 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_save(char **save)
{
	if (save)
	{
		free(*save);
		*save = NULL;
	}
}

int	get_line(char **line, char **save)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*save)[i] != '\0' && (*save)[i] != '\n')
		i++;
	if ((*save)[i] == '\n')
	{
		*line = ft_substr((*save), 0, i);
		temp = ft_strdup((*save) + i + 1);
		free(*save);
		*save = temp;
		if ((*save)[0] == '\0')
			free_save(save);
	}
	else
	{
		*line = ft_strdup(*save);
		free_save(save);
		return (0);
	}
	return (1);
}

int	return_l(char **line, char **save, int byte_lu)
{
	if (byte_lu < 0)
		return (-1);
	else if (byte_lu == 0 && *save == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (get_line(line, save));
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	char		*temp;
	static char	*save;
	int			byte_lu;

	if (fd < 0 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	byte_lu = read(fd, buf, BUFFER_SIZE);
	while (byte_lu > 0)
	{
		buf[byte_lu] = '\0';
		if (save == NULL)
			save = ft_strdup("");
		temp = ft_strjoin(save, buf);
		free(save);
		save = temp;
		if (ft_strchr(buf, '\n'))
			break ;
		byte_lu = read(fd, buf, BUFFER_SIZE);
	}
	return (return_l(line, &save, byte_lu));
}
