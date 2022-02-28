/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:01:08 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/03 16:45:00 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*collect_id_double_quote(t_lexer *lexer, char *value, t_var *var)
{
	lexer_next_char(lexer);
	if (!lexer->c)
	{
		if (value)
			free(value);
		return (NULL);
	}
	while (lexer->c != 34 && lexer->c)
	{
		if (lexer->c == '$')
			value = collect_id_env(lexer, value, var, 0);
		else
		{
			value = ft_realloc_char(value, lexer->c);
			lexer_next_char(lexer);
		}
		if (!lexer->c)
		{
			free(value);
			return (NULL);
		}
	}
	return (value);
}

static char	*collect_id_single_quote(t_lexer *lexer, char *value)
{
	lexer_next_char(lexer);
	if (!lexer->c)
	{
		if (value)
			free(value);
		return (NULL);
	}
	while (lexer->c != 39 && lexer->c)
	{
		value = ft_realloc_char(value, lexer->c);
		lexer_next_char(lexer);
		if (!lexer->c)
		{
			free(value);
			return (NULL);
		}
	}
	return (value);
}

char	*collect_id_string(t_lexer *lexer, char *value, t_var *var)
{
	if (lexer->c == 34)
	{
		value = collect_id_double_quote(lexer, value, var);
		if (!value && lexer->c != 34)
		{
			ft_putstr_fd("Unclosed double quotes\n", STDOUT_FILENO);
			return ("error_quote");
		}
		lexer_next_char(lexer);
	}
	if (lexer->c == 39)
	{
		value = collect_id_single_quote(lexer, value);
		if (!value && lexer->c != 39)
		{
			ft_putstr_fd("Unclosed single quotes\n", STDOUT_FILENO);
			return ("error_quote");
		}
		lexer_next_char(lexer);
	}
	return (value);
}

static char	*collect_id_env_norm(t_lexer *lexer, char *value)
{
	char	*itoa;

	itoa = ft_itoa(g_global);
	lexer_next_char(lexer);
	if (value)
	{
		value = ft_realloc(value, itoa);
		free(itoa);
		return (value);
	}
	else
		return (itoa);
}

char	*collect_id_env(t_lexer *lexer, char *value, t_var *var, int i)
{
	lexer_next_char(lexer);
	if (lexer->c == ' ' || !lexer->c)
	{
		value = ft_realloc_char(value, '$');
		return (value);
	}
	else if (lexer->c == '?')
		return (collect_id_env_norm(lexer, value));
	else
	{
		i = lexer->index;
		while (ft_isalpha(lexer->c) || ft_isnum(lexer->c) || lexer->c == '_')
			lexer_next_char(lexer);
		if (!value)
			value = ft_strdup(get_env(lexer->value, i, var));
		else
			value = ft_realloc(value, get_env(lexer->value, i, var));
	}
	return (value);
}
