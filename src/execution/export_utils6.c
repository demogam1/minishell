/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:55:08 by misaev            #+#    #+#             */
/*   Updated: 2021/11/03 15:27:03 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlen_var_arg(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (0);
	i++;
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j - 2);
}

t_lenv	*ft_lstdup(t_lenv *lst)
{
	t_lenv	*tmp;
	char	*quotes;
	int		i;

	i = 0;
	quotes = NULL;
	tmp = empty_list();
	while (lst)
	{
		if (count_equals(lst->var_env) == 0)
			quotes = ft_strdup(lst->var_env);
		else
			quotes = add_quote(lst->var_env);
		tmp = add_at(tmp, quotes, i, 0);
		lst = lst->next;
		free(quotes);
		i++;
	}
	return (tmp);
}
/* Free une cellule de la liste */

t_lenv	*free_at(t_lenv **lst, int pos, int i)
{
	t_lenv	*prec;
	t_lenv	*cur;

	cur = *lst;
	prec = *lst;
	if (is_empty_list(*lst))
		return (NULL);
	if (pos == 0)
	{
		lst = &(*lst)->next;
		free(cur->var_env);
		free(cur);
		return (*(lst));
	}
	while (i < pos)
	{
		prec = cur;
		cur = cur->next;
		i++;
	}
	prec->next = cur->next;
	free(cur->var_env);
	free(cur);
	return (*(lst));
}

/* EXTENSION FUNCTION FOR CD TO REDUCE LINES FOR NORMINETTE */

void	change_path(t_var *var, char *prix)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(NULL, 0);
	add_new(&var->env, cwd, prix);
	free(cwd);
}
