/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:28:34 by misaev            #+#    #+#             */
/*   Updated: 2021/11/03 18:31:51 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Chercher dans la une chaine de caractere une autre chaine de caractere*/
char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			j = 0;
			while (to_find[j] == str[i + j])
			{
				if (to_find[j + 1] == '\0')
				{
					return (str + i);
				}
				j++;
			}
			i++;
		}
	}
	return (0);
}

/* CETTE FONCTION PARCOURS COMPARE DEUX NOM DE VAR D ENVI ET RENVOI UN INT */
int	ft_strstr_int(char *str, char *to_find)
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
	return (1);
}

/* Liberer la liste */
void	free_list(t_lenv *lst)
{
	t_lenv	*tmp;

	tmp = NULL;
	while (lst)
	{
		tmp = lst->next;
		free (lst->var_env);
		free (lst);
		lst = tmp;
	}
	lst = NULL;
}

/* Calculer la longueur de la liste */

int	len_list(t_lenv *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

void	print_list(t_lenv *lst, int d)
{
	if (d)
	{
		while (lst)
		{
			if (ft_strstr_int(lst->var_env, "_=") == 1)
				lst = lst->next;
			if (lst == NULL)
				break ;
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(lst->var_env, 1);
			write(1, "\n", 2);
			lst = lst->next;
		}
	}
	else
	{
		while (lst)
		{
			ft_putstr_fd(lst->var_env, 1);
			write(1, "\n", 2);
			lst = lst->next;
		}
	}
}
