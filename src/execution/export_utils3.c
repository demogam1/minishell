/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:43:38 by misaev            #+#    #+#             */
/*   Updated: 2021/11/03 15:25:19 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	sev_extension(t_lenv **lst, t_lenv *prec,
	t_lenv *cur, char *temp_str)
{
	int	i;

	while (check_if_done(*lst) == 1)
	{
		i = 0;
		if (prec->var_env[i] == cur->var_env[i])
			while (prec->var_env[i] == cur->var_env[i])
				i++;
		if (prec->var_env[i] > cur->var_env[i])
		{
			temp_str = cur->var_env;
			cur->var_env = prec->var_env;
			prec->var_env = temp_str;
			prec = *lst;
			cur = (*lst)->next;
		}
		else
		{
			prec = cur;
			cur = cur->next;
		}
		if (cur == NULL)
			break ;
	}
}

void	sort_env_var(t_lenv **lst)
{
	t_lenv	*prec;
	t_lenv	*cur;
	char	*temp_str;

	temp_str = NULL;
	cur = *lst;
	prec = *lst;
	cur = cur->next;
	sev_extension(lst, prec, cur, temp_str);
}

static char	*actv(char *dest,
	char *new_dest_content, char *content_to_add, int i)
{
	if (dest[i])
	{
		i++;
		new_dest_content = ft_calloc(sizeof(char),
				(ft_strlen(content_to_add) + i + 1));
	}
	else
		new_dest_content = ft_calloc(sizeof(char),
				(ft_strlen(content_to_add) + i + 2));
	return (new_dest_content);
}

static char	*actv_2(char *new_dest_content, char *content_to_add, int i)
{
	int	j;

	j = 0;
	if (content_to_add == NULL)
		new_dest_content[i] = '\0';
	else
	{
		while (content_to_add[j] != '\0')
			new_dest_content[i++] = content_to_add[j++];
		new_dest_content[i] = '\0';
	}
	return (new_dest_content);
}

char	*add_content_to_var(char *dest, char *content_to_add, int i)
{
	char	*new_dest_content;

	new_dest_content = NULL;
	while (dest[i] != '=' && dest[i])
		i++;
	new_dest_content = actv(dest, new_dest_content, content_to_add, i);
	i = 0;
	while (dest[i] != '=' && dest[i])
	{
		new_dest_content[i] = dest[i];
		i++;
	}
	if (dest[i])
		new_dest_content[i] = dest[i];
	else
		new_dest_content[i] = '=';
	i++;
	new_dest_content = actv_2(new_dest_content, content_to_add, i);
	free (dest);
	return (new_dest_content);
}
