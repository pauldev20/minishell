/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:32:05 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/21 19:40:23 by mhedtman         ###   ########.fr       */
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

typedef struct s_cmd_table
{
	char		**cmd_array;
	char		***arg_array;
	char		**in;
	char		**in_type;
	char		**here_docs;
	char		**out;
	char		**out_type;
}	t_ct;

typedef struct s_minishell
{
	t_env		*envp;
	char		**cmd_array;
	int			sigint;
	int			exit_code;
	int			executing;
	pid_t		pid;
}	t_minishell;

t_minishell		g_minishell;

enum	e_minishell_errors {
	QUOTE = 1,
	BAD_FILE = 2,
	EXECUTE_ERROR = 3,
	CD = 4,
	SYNTAX_PIPE = 5,
	SYNTAX_IO = 6,
	CMD_NOT_FOUND = 7
};

void		print_arr(char **arr);

int			minishell(char **argv, char **envp);
char		**arr_dup(char **enviroment);

// BUILTINS
int			builtin_parser(char **argv, int argc);
int			builtin_echo(char **argv, int argc);
int			builtin_env(void);
int			builtin_export(char	**argv, int argc);
int			builtin_unset(char **argv, int argc);
int			builtin_pwd(void);
int			builtin_cd(char *path);
int			builtin_exit(char *exit_code);
char		**catch_builtins(char **cmds, int *i, int *offset);

//PARSER
char		**parse_input(char *input);
char		**lexer(char const *s, char c);
int			check_pipe_error(char *str);
void		**pipe_expander(char ***arr);

//HELPER + ERROR
char		**empty_arr(void);
int			get_pipe_amount(char **tokens);
int			array_len(char **array);
void		print_error(int errtype, char *params, int err);
bool		str_is_equal(char *str1, char *str2);

// FREE
void		free_cmd_table(t_ct *cmd_table);
void		free_array(char **array);
void		*free_arr(char **arr, int arr_count);

// ENV
t_env		*get_last(t_env *env);
t_env		*parse_array_to_env(char **env, t_env *minienviro);
t_env		*get_env_var(t_env *env, char *key);
char		**get_env_arr(t_env *list);
void		add_back(t_env **env, t_env *new);
void		add_at_index(t_env **list, t_env *el, int index);
void		remove_at_index(t_env **list, int index);
void		free_array(char	**array);
void		print_env(t_env	*env);
int			in_list(t_env *env, char *key);
int			set_env_var(t_env **env, char *key, char *value);

// EXPANDER
int			ft_word_len(char *str);
bool		check_dquotes(char *str);
bool		squotes_first(char *str, int limit);
bool		check_squotes(char *str);
char		*expand_vars(char *str);

// PROMT
char		*get_prompt(t_env *usr, t_env *pwd, t_env *home, int rtn_code);

// SIGNAL
void		handle_signal(int sig);

// EXECUTE
int			start_execute(char **arr);
int			get_pipe_amount(char **tokens);
char		**cut_start_stop(char **cmd, int start_stop[2]);

// EXECUTE INITS
t_ct		*memory_allocation_arrays(t_ct *exetable, char **tokens);
t_ct		*init_cmd_table(t_ct *exetable, \
				char **cmd_array, int st_st[2], int i);
t_ct		*get_cmd_table(char **token_array, char **cmd_array);
char		*get_cmd_array(char **cmds, char **tokens, int start, int stop);

// EXECUTE PREJOBS
char		**execute_prejobs(char **arr);
char		**get_cmd_arg_arr(char *cmd, char **args);
char		*join_ios(char **arr, int *old_i);
bool		syntax_pipe_error(char **tokens, int i);
bool		syntax_io_error(char **tokens, int i);

// IO INIT
char		*get_infile(char **cmd_array, \
				char **token_array, int start, int stop);
char		*get_outfile(char **cmd_array, \
				char **token_array, int start, int stop);
char		*get_infile_type(char **token_array, int start, int stop);
char		*get_outfile_type(char **token_array, int start, int stop);

// IO MODIFICATION
int			get_infile_fd(t_ct *exe_table, char *token, char *arr, int pipe);
int			get_outfile_fd(char *token, char *arr, int pipe);
bool		is_output_redirector(char *str);
bool		is_input_redirector(char *str);

// TOKEN MODIFICATION
char		**join_io_modifier(char **arr);
char		**get_token_array(char **arr);
char		**delete_io(char **arr, char **tokens, int *fd);

// HERE_DOCS
void		here_doc_execute(char **limiter);
bool		has_dollars(char *str);
char		**get_here_doc_limiters(char **arr);

// BUILTIN EXECUTER
bool		is_own_builtin(char *cmd);
int			execute_own_builtin(char *cmd, char **args);

// PIPEX
int			child_process(t_ct *execute_table, char **envp, int i);
int			execute(char *cmd, char **args, char **envp);

// TTY
char		*catch_tty(char *prompt);
char		*get_terminal_line(int fd);

#endif