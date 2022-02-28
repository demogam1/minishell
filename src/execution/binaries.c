/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 14:50:45 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/02 12:56:33 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmp_binaries(char *cmd_value, t_var *var)
{
	char const	*cmd_path;

	cmd_path = get_path(cmd_value, var);
	if (cmd_path)
	{
		if (!access(cmd_path, X_OK))
		{
			free((void *)cmd_path);
			return (1);
		}
	}
	return (0);
}
