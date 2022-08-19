/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:32:05 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/19 09:58:19 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "libft.h"

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

void	minishell(void);
char	**arr_dup(char **enviroment);

// BUILTINS
void	builtin_parser(char **array);
void	builtin_echo(char **str, int newline);
void	builtin_exit(void);
void	builtin_env(void);
void	builtin_export(char	**arguments);
void	builtin_unset(char *key);
void	builtin_pwd(void);

void	parse_input(char *input);

// ENV
void	add_back(t_env **env, t_env *new);
t_env	*get_last(t_env *env);
void	add_at_index(t_env **list, t_env *el, int index);
void	remove_at_index(t_env **list, int index);
void	free_array(char	**array);
t_env	*parse_array_to_env(char	**env);
void	print_env(t_env	*env);

#endif