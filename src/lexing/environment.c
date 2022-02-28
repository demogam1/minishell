/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:54:36 by pacey             #+#    #+#             */
/*   Updated: 2021/11/03 11:53:29 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *token_value, int i, t_var *var)
{
	char	*env;
	int		size;
	int		x;

	x = 0;
	size = i;
	if (ft_isalpha(token_value[size]) || token_value[size] == '_')
		size++;
	while (ft_isalpha(token_value[size]) || token_value[size] == '_'
		|| ft_isnum(token_value[size]))
		size++;
	env = ft_calloc((size - i) + 1, sizeof(char));
	if (!env)
		return (NULL);
	while (i < size)
	{
		env[x] = token_value[i];
		i++;
		x++;
	}
	env[x] = '\0';
	env = ft_getenv(env, var, 1);
	token_value = env;
	return (token_value);
}

static int	ft_strchr_env(char *str, char *to_find)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (str[i] == to_find[i])
			i++;
		else
			return (0);
	}
	if (!to_find[i])
		return (1);
	else
		return (0);
}

static char	*ft_str_chr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)str + i + 1);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)str + i);
	return (NULL);
}

char	*ft_getenv(char *env, t_var *var, int i)
{
	t_lenv	*tmp_lst;

	tmp_lst = var->env;
	while (tmp_lst)
	{
		if (ft_strchr_env(tmp_lst->var_env, env))
		{
			if (i)
				free(env);
			return (ft_str_chr(tmp_lst->var_env, '='));
		}
		tmp_lst = tmp_lst->next;
	}
	if (i)
		free(env);
	return (NULL);
}
