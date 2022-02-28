/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:37:56 by misaev            #+#    #+#             */
/*   Updated: 2021/11/03 14:27:12 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_quote_extension(char *arg, char *str, int i, int j)
{
	int		equals;

	equals = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=' && equals == 0 && arg[i + 1] == 0)
		{
			str[j++] = arg[i];
			str[j++] = '"';
			break ;
		}
		else if (arg[i] == '=' && equals == 0)
		{
			equals++;
			str[j++] = arg[i++];
			str[j++] = '"';
		}
		str[j++] = arg[i++];
	}
	str[j++] = '"';
	str[j++] = '\0';
	return (str);
}

char	*add_quote(char *arg)
{
	int		i;
	int		j;
	char	*str;

	str = ft_calloc(sizeof(char), ft_strlen(arg) + 3);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	str = add_quote_extension(arg, str, i, j);
	return (str);
}

t_lenv	*push_env_to_list(char **env)
{
	int		i;
	t_lenv	*lst;

	lst = empty_list();
	i = 0;
	while (env[i + 1])
		i++;
	while (env[i])
	{
		lst = add_and_push_to_env(lst, env[i], 0, 0);
		i--;
	}
	return (lst);
}

void	add_var_last(t_lenv **lst, char *str, int export)
{
	char	*rstr;
	char	**var;

	rstr = ft_strdup(str);
	var = ft_split(rstr, '=');
	if (check_if_arg_in_env(var[0], *lst) == 0 && export == 0)
	{
		free(rstr);
		free_tab(var);
		return ;
	}
	if (check_if_arg_in_env(rstr, *lst) != 0 && count_equals(rstr) > 0)
		add_new(lst, var[1], var[0]);
	else if (check_if_arg_in_env(rstr, *lst) == 0)
		add_at(*lst, rstr, len_list(*lst), 0);
	free(rstr);
	free_tab(var);
}

int	check_if_done(t_lenv *lst)
{
	t_lenv	*prec;

	while (lst)
	{
		prec = lst;
		lst = lst->next;
		if (lst == NULL)
			return (0);
		if (prec->var_env[0] > lst->var_env[0])
			return (1);
	}
	return (0);
}
