/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:04:00 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/03 14:40:45 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**init_builtin_lst(void)
{
	char	**blti_lst;

	blti_lst = ft_calloc(8, sizeof(char *));
	if (!blti_lst)
		return (NULL);
	blti_lst[0] = "echo";
	blti_lst[1] = "cd";
	blti_lst[2] = "pwd";
	blti_lst[3] = "export";
	blti_lst[4] = "unset";
	blti_lst[5] = "env";
	blti_lst[6] = "exit";
	blti_lst[7] = NULL;
	return (blti_lst);
}

int	cmp_builtins(char *value)
{
	int		i;
	char	**bltin_lst;

	if (!value)
		return (7);
	bltin_lst = init_builtin_lst();
	i = 0;
	while (bltin_lst[i])
	{
		if (ft_strcmp(bltin_lst[i], value) == 0)
		{
			free (bltin_lst);
			return (i);
		}
		i++;
	}
	free (bltin_lst);
	return (7);
}

int	pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(NULL, 0);
	if (buf == NULL)
	{
		g_global = 1;
		perror(buf);
	}
	else
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
	}
	if (g_global != 1)
		g_global = 0;
	return (g_global);
}

int	exit_cmd(t_tree *cmd, int i)
{
	if (cmd->size_args > 1)
	{
		while (cmd->args[1][i])
		{
			if (!ft_isnum(cmd->args[1][i]))
			{
				printf("exit\n");
				printf("exit: %s: numeric argument required\n", cmd->args[1]);
				g_global = 255;
				return (0);
			}
			i++;
		}
		g_global = ft_atoi(cmd->args[1]);
	}
	else
		g_global = 0;
	if (cmd->size_args > 2)
	{
		printf("exit\n");
		printf("exit: too many arguments\n");
		g_global = 1;
		return (1);
	}
	return (0);
}
