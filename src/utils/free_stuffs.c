/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuffs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:23:15 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/03 18:41:12 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	free_token(t_token *token)
{
	if (token->type > 0 && token->type < 9)
		free(token->value);
	token->value = NULL;
	token->next = NULL;
	token->prev = NULL;
	free(token);
}

void	free_parser(t_pars *parser)
{
	parser->current_tok = parser->first_tok;
	while (parser->current_tok)
	{
		parser->first_tok = parser->current_tok;
		parser->current_tok = parser->current_tok->next;
		free_token(parser->first_tok);
	}
	free(parser->lexer);
	free(parser);
}

void	free_tree(t_tree *tree)
{
	free(tree->f_cmd);
	if (tree->cmd_type >= 0 && tree->cmd_type <= 10)
		free(tree->cmd_value);
	if (tree->size_args)
		free_tab(tree->args);
	if (tree->size_red)
		free_tab(tree->red);
	free(tree);
}

void	free_all(t_tree **root, char **split, char *line)
{
	int	i;

	i = 0;
	while (root[i])
	{
		free_tree(root[i]);
		i++;
	}
	free(root);
	free_tab(split);
	free(line);
}
