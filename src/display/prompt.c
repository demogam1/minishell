/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:03:08 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/03 14:55:40 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_invite(t_var *var)
{
	char	*invite;

	invite = NULL;
	if (ft_getenv("USER", var, 0))
	{
		invite = ft_getenv("USER", var, 0);
		invite = ft_strjoin(invite, "@");
		invite = ft_realloc(invite, ft_getenv("USER", var, 0));
	}
	else
		invite = ft_strdup("Fallait pas unset USER!!!!");
	return (invite);
}

char	*prompt_color(t_var *var)
{
	char const	*absolute_p;
	char		**relative_p;
	char		*invite;
	int			i;

	i = 0;
	invite = NULL;
	invite = get_invite(var);
	absolute_p = ft_getenv("PWD", var, 0);
	if (!absolute_p)
		absolute_p = "";
	relative_p = ft_split(absolute_p, '/');
	invite = ft_realloc(invite, ":~/");
	while (relative_p[i])
		i++;
	if (i > 0)
		invite = ft_realloc(invite, relative_p[i - 1]);
	invite = ft_realloc(invite, "$ ");
	free_tab(relative_p);
	return (invite);
}

char	*display_prompt(t_var *var)
{
	char	*prompt;
	char	*line;

	prompt = prompt_color(var);
	line = readline(prompt);
	free(prompt);
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
}
