/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:01:54 by misaev            #+#    #+#             */
/*   Updated: 2021/11/03 15:25:25 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			j++;
		i++;
	}
	return (j);
}

int	count_equals(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			j++;
		i++;
	}
	return (j);
}

int	check_export_args_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' || str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 1 || str[i] == '_'
			|| (ft_isnum(str[i]) == 1 && i > 0))
			i++;
		else if ((str[i] == '=' && i > 0)
			|| (str[i] == '\0' && i > 0))
			return (0);
		else
			return (1);
	}
	return (0);
}

int	check_if_arg_in_env(char *var_name, t_lenv *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		if (ft_strstr_int(lst->var_env, var_name) != 0)
			return (i);
		lst = lst->next;
		i++;
	}
	return (0);
}

void	add_new(t_lenv **lst, char *new_content, char *var_dest)
{
	t_lenv	*temp;

	temp = *lst;
	while (temp != NULL)
	{
		if (ft_strstr_int(temp->var_env, var_dest) != 0)
		{
			temp->var_env = add_content_to_var(temp->var_env, new_content, 0);
			break ;
		}
		temp = temp->next;
	}
	if (temp == NULL)
	{
		*lst = add_at(*lst, var_dest, 0, 0);
		add_new(lst, getcwd(NULL, 0), var_dest);
	}
}
