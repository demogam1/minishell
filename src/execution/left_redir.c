/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:18:03 by hkrifa            #+#    #+#             */
/*   Updated: 2021/11/02 17:25:58 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_exit(int sig)
{
	if (sig == SIGQUIT && g_global > 258)
	{
		ft_putstr_fd("\e[2K", 1);
		ft_putstr_fd("\r> ", 1);
	}
	if ((sig == SIGINT) && g_global > 258)
	{
		if (!kill(g_global, SIGTERM))
			g_global = 1;
		printf("\e[2K");
		printf("\n");
	}
}

int	left_redir(t_tree **cmds, int i, int j)
{
	int	filein;

	filein = open(cmds[i]->red[j + 1], O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("open");
		g_global = 1;
		return (g_global);
	}
	if (j == 0)
	{
		dup2(filein, 0);
		close(filein);
	}
	return (0);
}

int	double_left_redir(t_tree **cmds, int i, int j)
{
	int	filein;

	(void)cmds;
	(void)i;
	(void)j;
	filein = open("temp.txt", O_RDONLY, 0777);
	if (filein == -1)
	{
		perror("open");
		g_global = 1;
		return (g_global);
	}
	dup2(filein, 0);
	close(filein);
	if (!cmds[i]->cmd_value && cmds[i]->red[j + 2] == NULL)
		exit (0);
	return (0);
}

static int	open_heredoc(t_tree **cmds, int i, int j, t_var *var)
{
	var->pid2 = fork();
	g_global = var->pid2;
	if (!var->pid2)
	{
		while (cmds[i]->heredoc[j] != NULL)
		{
			var->temp = open("temp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
			while (write(1, "> ", ft_strlen("> "))
				&& get_next_line(0, &var->line) > 0
				&& (ft_strcmp(var->line, cmds[i]->heredoc[j + 1]) != 0))
			{
				write(var->temp, var->line, ft_strlen(var->line));
				write(var->temp, "\n", 1);
				free(var->line);
			}
			j += 2;
		}
		close(var->temp);
		exit(0);
	}
	signal(SIGINT, handler_exit);
	signal(SIGQUIT, handler_exit);
	waitpid(var->pid2, &var->status, 0);
	cmds[i]->sig = WTERMSIG(var->status);
	return (1);
}

void	loop_double_redir(t_tree **cmds, int i, t_var *var)
{
	int	j;

	j = 0;
	cmds[i]->heredoc = get_tab(cmds[i]);
	open_heredoc(cmds, i, j, var);
	free(cmds[i]->heredoc);
}
