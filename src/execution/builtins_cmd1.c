/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misaev <misaev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:25:27 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/03 15:27:39 by misaev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_export_norm(t_tree *tree, t_var *var, int i, int e)
{
	while (tree->args[i])
	{
		if (check_export_args_str(tree->args[i]) == 1)
		{
			printf("export: `%s': not a valid identifier\n", tree->args[i]);
			if (tree->size_args - i == 1)
			{
				g_global = 1;
				return (g_global);
			}
		}
		else
		{
			if (count_equals(tree->args[i]) || !(count_equals(tree->args[i])
					&& !(check_if_arg_in_env(tree->args[i], var->env))))
				add_var_last(&var->env, tree->args[i], e);
		}
		i++;
	}
	return (g_global);
}

int	exec_export(t_tree *tree, t_var *var)
{
	int		i;
	int		e;
	t_lenv	*lst;

	e = 0;
	i = 0;
	if (tree->cmd_type == tree_export)
	{
		i = 1;
		e = 1;
	}
	if (tree->size_args > 1 && tree->cmd_type == tree_export)
		exec_export_norm(tree, var, i, e);
	else if (tree->cmd_type == tree_export && tree->size_args == 1)
	{
		lst = ft_lstdup(var->env);
		sort_env_var(&lst);
		print_list(lst, 1);
		free_list(lst);
	}
	if (g_global == 1)
		g_global = 1;
	else
		g_global = 0;
	return (g_global);
}

int	exec_env(t_tree *tree, t_var *var)
{
	if (tree->size_args == 1)
	{
		print_list(var->env, 0);
		g_global = 0;
		return (g_global);
	}
	else
	{
		g_global = 127;
		return (g_global);
	}
}

int	exec_unset(t_tree *tree, t_var *var)
{
	int		i;
	int		j;
	t_lenv	*temp_lst;

	i = 1;
	if (tree->size_args > 1)
	{
		while (tree->args[i])
		{
			j = 0;
			temp_lst = var->env;
			while (temp_lst)
			{
				if (ft_strstr_int(temp_lst->var_env, tree->args[i]) == 1)
				{
					var->env = free_at(&var->env, j, 0);
					break ;
				}
				j++;
				temp_lst = temp_lst->next;
			}
			i++;
		}
	}
	return (0);
}

int	right_redir_builtins(t_tree *cmd)
{	
	int	fileout;
	int	j;

	j = 0;
	while (cmd->red[j] != NULL)
	{
		if (!ft_strcmp(cmd->red[j], ">") || !ft_strcmp(cmd->red[j], ">>"))
		{
			fileout = open(cmd->red[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fileout == -1)
			{
				perror("open");
				return (0);
			}
			if (cmd->red[j + 2] == NULL)
			{
				cmd->save = dup(1);
				dup2(fileout, 1);
				close(fileout);
			}
			j += 2;
		}
	}
	return (1);
}
