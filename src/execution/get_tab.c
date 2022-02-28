/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:14:15 by hkrifa            #+#    #+#             */
/*   Updated: 2021/11/02 17:27:32 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_strs(char **tab)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (tab[i] != NULL)
	{
		if (!ft_strcmp(tab[i], "<<"))
			count++;
		i++;
	}
	return (count);
}

char	**get_tab(t_tree *cmd)
{
	int		k;
	int		l;
	int		count;
	char	**heredoc;

	k = 0;
	l = 0;
	count = count_strs(cmd->red);
	heredoc = malloc(sizeof(heredoc) * (count + count) + 1);
	k = 0;
	while (cmd->red[k] != NULL)
	{
		if (!ft_strcmp(cmd->red[k], "<<"))
		{
			heredoc[l] = cmd->red[k];
			k++;
			l++;
			heredoc[l] = cmd->red[k];
			l++;
		}
		k++;
	}
	heredoc[l] = NULL;
	return (heredoc);
}
