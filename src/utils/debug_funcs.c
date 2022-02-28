/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:53:12 by hkrifa            #+#    #+#             */
/*   Updated: 2021/10/21 12:17:06 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		printf("[ %s ]", strs[i]);
		i++;
	}
}

void	print_token(t_token *token)
{
	printf("TOKEN TYPE : [ %d ]\n", token->type);
	printf("TOKEN VALUE : [ %s ]\n", token->value);
}

void	print_tree(t_tree *tree)
{
	printf("FULL CMD = [ %s ]\n", tree->f_cmd);
	printf("NAME OF CMD = [ %s ]\n", tree->cmd_value);
	printf("TYPE OF CMD = [ %d ]\n", tree->cmd_type);
	if (tree->size_args)
	{
		printf("ARGS = ");
		print_strs(tree->args);
		printf("\n");
	}
	if (tree->size_red)
	{
		printf("REDIRECTIONS = ");
		print_strs(tree->red);
		printf("\n");
	}
	printf("SIZE ARGS = [ %d ]\n", tree->size_args);
	printf("SIZE REDIR = [ %d ]\n", tree->size_red);
	printf("------------------------------------\n");
}

void	print_trees(t_tree **root)
{
	int	i;

	i = 0;
	while (root[i] != NULL)
	{
		print_tree(root[i]);
		i++;
	}
}
