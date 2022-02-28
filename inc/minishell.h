/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkrifa <hkrifa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:45:43 by pjacob            #+#    #+#             */
/*   Updated: 2021/11/03 18:39:34 by hkrifa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <stddef.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_lexer
{
	char	c;
	int		index;
	char	*value;
}				t_lexer;

typedef struct s_token
{
	enum e_type
	{
		token_cmd = 1,
		token_id,
		token_env,
		token_file,
		token_sred_l,
		token_sred_r,
		token_dred_l,
		token_dred_r,
		token_EOL,
		token_error
	}	type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_pars
{
	t_lexer	*lexer;
	t_token	*current_tok;
	t_token	*prev_tok;
	t_token	*first_tok;
}				t_pars;

typedef struct s_tree
{
	enum	e_cmd_type
	{
		tree_echo = 0,
		tree_cd,
		tree_pwd,
		tree_export,
		tree_unset,
		tree_env,
		tree_exit,
		tree_exportargs,
		tree_execve,
		tree_path,
		tree_nocmd,
	}		cmd_type;
	char	*cmd_value;
	char	*f_cmd;
	char	**args;
	char	**red;
	int		size_args;
	int		size_red;
	int		e;
	int		z;
	int		save;
	int		sig;
	char	**heredoc;
}				t_tree;

typedef struct s_env
{
	char			*var_env;
	struct s_env	*next;
}				t_lenv;

typedef struct s_var
{
	int			i;
	int			temp;
	int			status;
	pid_t		pid;
	pid_t		pid2;
	t_lenv		*env;
	char		*line;
	char		**envp;
}				t_var;

extern int	g_global;

/* *****DISPLAY FUNCTIONS ****** */
char	*prompt_color(t_var *var);
int		signal_set(t_tree *tree);
int		error_redirections(t_tree *tree);
int		error_handler(t_tree *tree);
int		check_forbidden_char(char *line);
char	*display_prompt(t_var *var);
void	handler_signals(int sig);
void	handler_child(int sig);
void	rl_replace_line(const char *text, int clear_undo);

/* *******EXECUTION FUNCTIONS****** */

/* FONCTIONS DE PIPES ET REDIRECTIONS */
void	exec_pipes(t_tree **cmds, t_var *var);
int		redirections(t_tree **cmds, int i);
int		right_redir(t_tree **cmds, int i, int j);
int		left_redir(t_tree **cmds, int i, int j);
void	loop_double_redir(t_tree **cmds, int i, t_var *var);
int		double_right_redir(t_tree **cmds, int i, int j);
int		double_left_redir(t_tree **cmds, int i, int j);
char	**get_tab(t_tree *cmd);

/* ------FONCTIONS BUILTINS--------- */
int		cmp_builtins(char *value);
int		builtins_cmd(t_tree *cmd, t_var *var);
int		cmp_binaries(char *value, t_var *var);
char	*ft_getenv(char *env, t_var *var, int i);
char	*get_path(char *cmd, t_var *var);
int		echo(t_tree *tree, int i);
int		cd(t_var *var, char *path);
int		pwd(void);
int		exit_cmd(t_tree *cmd, int i);
int		exec_export(t_tree *tree, t_var *var);
int		exec_env(t_tree *tree, t_var *var);
int		echo_option(t_tree *tree, int i);
int		builtins_redir(t_tree *cmd);
void	loop_double_redirs(t_tree *cmds, t_var *var);
int		open_heredoc_builtins(char **heredoc, int j, t_var *var);
int		double_left_redirs(t_tree *cmd, int j);
int		left_redirs(t_tree *cmd, int j);

/*FONCTION POUR LISTE CHAINEE EXPORT */
int		len_list(t_lenv *lst);
void	free_list(t_lenv *lst);
t_lenv	*empty_list(void);
int		is_empty_list(t_lenv *lst);
t_lenv	*add_at(t_lenv *lst, char *str, int pos, int i);

/*FONCTIONS NECESSAIRE POUR LE BUILTIN EXPORT*/
char	*ft_strstr(char *str, char *to_find);
void	print_list(t_lenv *lst, int i);
char	*add_quote(char *arg);
t_lenv	*push_env_to_list(char **env);
t_lenv	*add_and_push_to_env(t_lenv *lst, char *str, int pos, int i);
void	add_var_last(t_lenv **lst, char *str, int export);
int		check_if_done(t_lenv *lst);
void	sort_env_var(t_lenv **lst);
void	add_new(t_lenv **lst, char *new_content, char *var_dest);
char	*add_content_to_var(char *dest, char *content_to_add, int i);
int		check_export_args_tab(char **arg);
int		count_quotes(char *str);
int		count_equals(char *str);
int		check_export_args_str(char *str);
int		count_tab_nbr(char **args);
int		check_if_arg_in_env(char *var_name, t_lenv *d_env);
int		strlen_var_arg(char *str);
int		ft_strstr_int(char *str, char *to_find);
t_lenv	*ft_lstdup(t_lenv *lst);

/* FONCTION POUR UNSET */
int		exec_unset(t_tree *tree, t_var *var);
t_lenv	*free_at(t_lenv **lst, int pos, int i);
/* EXTENSION FUNCTIONS */
void	change_path(t_var *var, char *prix);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char *s, unsigned int start, unsigned int len);
int		get_next_line(int fd, char **line);

/* *************LEXING FUNCTIONS**************** */
int		count_env_in_string(t_token *token);
char	*get_env(char *token_value, int i, t_var *var);
char	*get_str_with_env(t_token *token, t_var *var);
t_token	*init_token(int type, char *value);
t_token	*get_next_token(t_lexer	*lexer, t_var *var);
t_lexer	*init_lexer(char *value);
void	lexer_next_char(t_lexer *lexer);
t_token	*lexer_collect_id(t_lexer *lexer, t_var *var);
char	*collect_id_string(t_lexer *lexer, char *value, t_var *var);
char	*collect_id_env(t_lexer *lexer, char *value, t_var *var, int i);

/* ***************PARSING FUNCTIONS************** */
int		count_pipes(char const *line, char c, int i);
char	**ft_split_pipe(char *s, char c);
t_pars	*init_pars(t_lexer *lexer, t_var *var);
void	parser_next_token(t_pars *parser, t_var *var);
void	parser_define_more_token(t_pars *parser);
t_tree	*init_tree(int type, char *cmd);
t_tree	*create_trees(char *cmd, t_var *var);

/* ************UTILS FUNCTIONS************* */
void	print_token(t_token *token);
void	print_strs(char **strs);
void	print_tree(t_tree *tree);
void	print_trees(t_tree **root);
void	free_tab(char **tab);
void	free_token(t_token *token);
void	free_parser(t_pars *parser);
void	free_tree(t_tree *tree);
void	free_all(t_tree **root, char **split, char *line);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, const char *src);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_isalpha(char c);
void	ft_putstr_fd(char *str, int fd);
char	*ft_strcpy(char *cpy, char *src);
char	*ft_realloc_char(char *src, char c);
void	*ft_calloc(int size, int type);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(const char *s);
int		ft_is_ascii(char c);
char	*ft_realloc(char *s1, char *s2);
void	ft_putchar_fd(char c, int fd);
int		ft_isnum(char c);
int		ft_sch_forbidden_char(char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *str);
int		ft_is_exportargs(char *str);
int		ft_isdigit(char *str);
int		check_forbidden_pipe_utils(char *line);

#endif
