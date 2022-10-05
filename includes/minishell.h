/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:32:05 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/05 16:39:52 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct s_minishell
{
	t_env	*envp;
	char	**cmd_array;
}	t_minishell;

t_minishell		g_minishell;

enum	e_minishell_errors {
	QUOTE = 1
};

void	print_arr(char **arr);

void	minishell(int argc, char **argv, char **envp);
char	**arr_dup(char **enviroment);

// BUILTINS
int		builtin_parser(char **argv, int argc, int pipe_amount);
int		builtin_echo(char **argv, int argc);
void	builtin_env(void);
int		builtin_export(char	**argv, int argc);
int		builtin_unset(char **argv, int argc);
int		builtin_pwd(void);
int		builtin_cd(char *path, int pipe_amount);
void	builtin_exit(void);

void	*parse_input(char *input);

void	*print_error(int errtype, char *params, int err);

// ENV
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
char	**get_token_array(char **arr);
int		get_pipe_amount(char **tokens);
char	**delete_io(char **arr, char **tokens);
char	**cut_start_stop(char **cmd, int start_stop[2]);

// IO MODIFICATION
int		get_infile_fd(char **token, char **arr);
int		get_outfile_fd(char **token, char **arr);
bool	is_output_redirector(char *str);
bool	is_input_redirector(char *str);

// TOKEN MODIFICATION
char	**join_io_modifier(char **arr);
int		get_pipe_amount(char **tokens);
char	**get_token_array(char **arr);
char	**delete_io(char **arr, char **tokens);

// HERE_DOCS
void	here_doc_execute(char *limiter, char **arr);

// BUILTIN EXECUTER
bool	is_own_builtin(char **cmd, int start_stop[2]);
void	execute_own_builtin(char **cmd, int start_stop[2]);

// PIPEX
void	child_process(char **cmd_args, char **envp, int start_stop[2]);
void	execute(char **cmd, char **envp, int start_stop[2]);

// TTY
char	*catch_tty(char *prompt);
char	*get_terminal_line(int fd);

#endif