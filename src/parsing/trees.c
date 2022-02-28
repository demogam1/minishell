/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 15:58:43 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/03 18:42:13 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*init_tree(int type, char *cmd)
{
	t_tree	*new_tree;
	char	*full_cmd;

	new_tree = ft_calloc(1, sizeof(t_tree));
	if (!new_tree)
		return (NULL);
	full_cmd = ft_strdup(cmd);
	new_tree->cmd_type = type;
	new_tree->f_cmd = full_cmd;
	new_tree->cmd_value = NULL;
	new_tree->args = NULL;
	new_tree->red = NULL;
	new_tree->size_args = 0;
	new_tree->size_red = 0;
	return (new_tree);
}

static void	get_args(t_tree *tree, t_pars *parser)
{
	int	i;

	i = 0;
	tree->args = ft_calloc(tree->size_args + 1, sizeof(char *));
	if (!tree->args)
	{
		tree->args = NULL;
		return ;
	}
	parser->current_tok = parser->first_tok;
	while (parser->current_tok)
	{
		if ((parser->current_tok->type > 0 && parser->current_tok->type < 4)
			&& parser->current_tok->value)
		{
			tree->args[i] = ft_strdup(parser->current_tok->value);
			i++;
		}
		parser->current_tok = parser->current_tok->next;
	}
	tree->args[i] = NULL;
}

static void	get_args_and_red(t_tree *tree, t_pars *parser, int i)
{
	if (tree->size_args > 0)
		get_args(tree, parser);
	if (tree->size_red > 0)
	{
		i = 0;
		tree->red = ft_calloc(tree->size_red + 1, sizeof(char *));
		if (!tree->red)
		{
			tree->red = NULL;
			return ;
		}
		parser->current_tok = parser->first_tok;
		while (parser->current_tok)
		{
			if (parser->current_tok->type > 3 && parser->current_tok->type < 9
				&& tree->cmd_type != tree_exportargs)
			{
				tree->red[i] = ft_strdup(parser->current_tok->value);
				i++;
			}
			parser->current_tok = parser->current_tok->next;
		}
		tree->red[i] = NULL;
	}
}

static void	get_type_and_size(t_tree *tree, t_pars *parser, t_var *var)
{
	parser->current_tok = parser->first_tok;
	while (parser->current_tok->type != token_EOL)
	{
		if (parser->current_tok->type == token_cmd)
		{
			if (cmp_builtins(parser->current_tok->value) < 7)
				tree->cmd_type = cmp_builtins(parser->current_tok->value);
			else if (cmp_binaries(parser->current_tok->value, var))
				tree->cmd_type = tree_execve;
			else if (parser->current_tok->value[0] == '.'
				|| parser->current_tok->value[0] == '/')
				tree->cmd_type = tree_path;
			else if (ft_is_exportargs(parser->current_tok->value))
				tree->cmd_type = tree_exportargs;
			tree->cmd_value = ft_strdup(parser->current_tok->value);
		}
		if ((parser->current_tok->type > 0 && parser->current_tok->type < 4)
			&& parser->current_tok->value)
			tree->size_args++;
		if ((parser->current_tok->type > 3 && parser->current_tok->type < 9)
			&& tree->cmd_type != tree_exportargs)
			tree->size_red++;
		parser->current_tok = parser->current_tok->next;
	}
}

t_tree	*create_trees(char *cmd, t_var *var)
{
	t_tree		*tree;
	t_lexer		*lexer;
	t_pars		*parser;

	tree = init_tree(tree_nocmd, cmd);
	lexer = init_lexer(cmd);
	parser = init_pars(lexer, var);
	while (parser->current_tok->type != token_EOL)
	{
		if (parser->current_tok->type == token_error)
		{
			g_global = 258;
			free_parser(parser);
			free_tree(tree);
			return (NULL);
		}
		parser_next_token(parser, var);
	}
	parser_define_more_token(parser);
	get_type_and_size(tree, parser, var);
	get_args_and_red(tree, parser, 0);
	free_parser(parser);
	return (tree);
}
