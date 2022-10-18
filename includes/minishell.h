/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:32:05 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/18 14:06:58 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <limits.h>
# include "libft.h"
# include <sys/stat.h>
# include <fcntl.h>


typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
}	t_env;

typedef struct s_execute_table
{
	char		**cmd_array;
	char		**infiles;
	char		**infile_type;
	char		**here_docs;
	char		**outfiles;
	char		**outfile_type;
}	t_execute_table;

typedef struct s_minishell
{
	t_env		*envp;
	char		**cmd_array;
	int			sigint;
	int			exit_code;
	int			executing;
}	t_minishell;

t_minishell		g_minishell;

enum	e_minishell_errors {
	QUOTE = 1,
	BAD_FILE = 2,
	EXECUTE_ERROR = 3,
	CD = 4,
	SYNTAX_PIPE = 5,
	SYNTAX_IO = 6
};

void	print_arr(char **arr);

int		minishell(int argc, char **argv, char **envp);
char	**arr_dup(char **enviroment);

// BUILTINS
int		builtin_parser(char **argv, int argc, int pipe_amount);
int		builtin_echo(char **argv, int argc);
void	builtin_env(void);
int		builtin_export(char	**argv, int argc);
int		builtin_unset(char **argv, int argc);
int		builtin_pwd(void);
int		builtin_cd(char *path, int pipe_amount);
int		builtin_exit(char *exit_code);

char	**parse_input(char *input);

void	*print_error(int errtype, char *params, int err);

// ENV
char	**get_env_arr(t_env *list);
void	add_back(t_env **env, t_env *new);
t_env	*get_last(t_env *env);
void	add_at_index(t_env **list, t_env *el, int index);
void	remove_at_index(t_env **list, int index);
void	free_array(char	**array);
t_env	*parse_array_to_env(char **env, t_env *minienviro);
void	print_env(t_env	*env);
t_env	*get_env_var(t_env *env, char *key);
int		in_list(t_env *env, char *key);
int		set_env_var(t_env **env, char *key, char *value);

char	**lexer(char const *s, char c);
void	**pipe_expander(char ***arr);
void	*free_arr(char **arr, int arr_count);

// EXPANDER
int		ft_word_len(char *str);
bool	check_dquotes(char *str);
bool	squotes_first(char *str, int limit);
bool	check_squotes(char *str);
char	*expand_vars(char *str);

// PROMT
char	*get_prompt(t_env *usr, t_env *pwd, t_env *home);

// SIGNAL
void	handle_signal(int sig);

// EXECUTE
int		start_execute(char **arr);
int		get_pipe_amount(char **tokens);
char	**cut_start_stop(char **cmd, int start_stop[2]);
char	**execute_prejobs(char **arr);

// IO MODIFICATION
int		get_infile_fd(t_execute_table *exe_table, char *token, char *arr, int pipe);
int		get_outfile_fd(char *token, char *arr, int pipe);
bool	is_output_redirector(char *str);
bool	is_input_redirector(char *str);

// TOKEN MODIFICATION
char	**join_io_modifier(char **arr);
int		get_pipe_amount(char **tokens);
char	**get_token_array(char **arr);
char	**delete_io(char **arr, char **tokens, int *fd);

// HERE_DOCS
void	here_doc_execute(t_execute_table *exe_table);
char	**get_here_doc_limiters(char **arr);
bool	str_is_equal(char *str1, char *str2);

// BUILTIN EXECUTER
bool	is_own_builtin(char **cmd);
int		execute_own_builtin(char **cmd);

// PIPEX
int		child_process(t_execute_table *execute_table, char **envp, int i);
int		execute(char **cmd, char **envp);

// TTY
char	*catch_tty(char *prompt);
char	*get_terminal_line(int fd);

#endif