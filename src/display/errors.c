/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:26:55 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/03 16:13:15 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	signal_set(t_tree *tree)
{
	if (tree->size_args)
	{
		if (tree->cmd_type == tree_nocmd)
		{
			if (!ft_strcmp(tree->f_cmd, "$?")
				|| !ft_strcmp(tree->f_cmd, "$? + $?"))
				printf("minishell: %d: command not found\n", g_global);
			else if (!ft_strcmp(tree->f_cmd, "$?+$?"))
				printf("minishell: %d+%d: command not found\n",
					g_global, g_global);
			else
			{				
				printf("minishell: ");
				if (tree->size_args)
					printf("%s", tree->args[0]);
				printf(": command not found\n");
			}
			g_global = 127;
			return (g_global);
		}
	}
	return (0);
}

int	error_redirections(t_tree *tree)
{
	int	i;

	i = 0;
	if (tree->size_red)
	{
		while (i < tree->size_red)
		{
			if ((!ft_strcmp(tree->red[i], "<") || !ft_strcmp(tree->red[i], "<<")
					|| !ft_strcmp(tree->red[i], ">")
					|| !ft_strcmp(tree->red[i], ">>"))
				&& i + 1 < tree->size_red)
				i += 2;
			else
			{
				g_global = 258;
				return (printf("Syntax error near token \"%s\"\n", tree->red[i]));
			}
		}
	}
	return (0);
}

int	error_handler(t_tree *tree)
{
	int	ret;
	int	i;

	i = 1;
	ret = 0;
	if (tree->size_args)
		ret = signal_set(tree);
	if (tree->size_red && ret == 0)
		ret = error_redirections(tree);
	while (i < tree->size_red)
	{
		if (tree->red[i][0] != '<' && tree->red[i][0] != '>')
			i += 2;
		else
		{
			g_global = 258;
			ret = printf("Syntax error unexpected token\n");
			return (ret);
		}
	}	
	return (ret);
}

static int	check_forbidden_pipe(char *line)
{
	int	i;

	i = 0;
	if (line[i] && (line[i] == '|' || line[i] == ' '))
		if (check_forbidden_pipe_utils(line))
			return (1);
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] && line[i + 1] == '|')
		{
			g_global = 258;
			ft_putstr_fd("Syntax error invalid pipe\n", STDOUT_FILENO);
			return (g_global);
		}
		i++;
	}
	if (line[i - 1] == '|')
	{
		g_global = 258;
		ft_putstr_fd("Syntax error invalid pipe\n", STDOUT_FILENO);
		return (g_global);
	}
	return (0);
}

int	check_forbidden_char(char *line)
{
	int		i;
	char	c;
	int		ret;

	i = 0;
	while (line[i])
	{
		if (ft_sch_forbidden_char(line[i]))
		{
			g_global = 1;
			ft_putstr_fd("Invalid character\n", STDOUT_FILENO);
			return (g_global);
		}
		if (line[i] != ' ')
			c = line[i];
		i++;
	}
	ret = check_forbidden_pipe(line);
	return (ret);
}
