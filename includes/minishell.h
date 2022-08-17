/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:32:05 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/17 22:22:36 by pgeeser          ###   ########.fr       */83c1f02ffaa9d1fe396a6ede52b6fbd2dc837
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_env
{
	t_env	*next;
	char	*key;
	char	*value;
}	t_env;

typedef struct s_minishell
{
	char	**envp;
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

void	parse_input(char *input);

#endif