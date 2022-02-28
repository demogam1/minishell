/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:20:04 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/03 11:52:34 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_tab_path(char **tab, char *cmd)
{
	int	i;

	i = -1;
	while (tab[++i])
		tab[i] = ft_realloc(tab[i], "/");
	i = -1;
	while (tab[++i])
		tab[i] = ft_realloc(tab[i], cmd);
	return (tab);
}

char	*get_path(char *cmd, t_var *var)
{
	char	*path;
	char	*good_path;
	char	**tab;
	int		i;

	path = ft_getenv("PATH", var, 0);
	if (path)
	{
		tab = ft_split(path, ':');
		tab = get_tab_path(tab, cmd);
		i = -1;
		while (tab[++i])
		{
			good_path = ft_strdup(tab[i]);
			if (access(tab[i], F_OK) == 0)
			{
				free_tab(tab);
				return (good_path);
			}
			free(good_path);
		}
		free_tab(tab);
	}
	return (NULL);
}
