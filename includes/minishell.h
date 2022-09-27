/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:32:05 by mhedtman          #+#    #+#             */
/*   Updated: 2022/09/27 14:15:52 by mhedtman         ###   ########.fr       */
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

void	minishell(int argc, char **argv, char **envp);
char	**arr_dup(char **enviroment);

// BUILTINS
int		builtin_parser(char **argv, int argc);
int		builtin_echo(char **argv, int argc);
void	builtin_exit(void);
void	builtin_env(void);
int		builtin_export(char	**argv, int argc);
int		builtin_unset(char **argv, int argc);
int		builtin_pwd(void);

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
char	*expand_vars(char *str);
void	**pipe_expander(char ***arr);
void	*free_arr(char **arr, int arr_count);

// PROMT
char	*get_promt(t_env *usr, t_env *pwd, t_env *home);

// SIGNAL
void	handle_signal(int sig);

// EXECUTE
int		handle_execute(char **arr);

// PIPEX
void	child_process(char *argv, char **envp);
void	execute(char *argv, char **envp);

#endif