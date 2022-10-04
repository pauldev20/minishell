/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:07:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/04 11:15:43 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO DO:
	- CATCH ^C AND ^\
	- ADD HERE_DOC
	- ADD OWN ENVP IN EXECUTE
	- ADD REST OF BUILTINS
	- DELETE HERE_DOC AFTER PROGRAMM?
	*/

static int	if_chars(char *str)
{
	int	chars;

	chars = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str <= 124 && *str >= 33)
			chars++;
		str++;
	}
	return (chars > 0);
}

static void	init_env(char **argv)
{
	char	*str;
	t_env	*el;

	el = get_env_var(g_minishell.envp, "SHLVL");
	if (!el)
		set_env_var(&g_minishell.envp, "SHLVL", "1");
	else
		set_env_var(&g_minishell.envp, "SHLVL",
			ft_itoa(ft_atoi(el->value) + 1));
	str = getcwd(NULL, 0);
	set_env_var(&g_minishell.envp, "PWD", str);
	free(str);
	el = get_env_var(g_minishell.envp, "PATH");
	if (!el)
		set_env_var(&g_minishell.envp, "PATH",
			"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin");
	el = get_env_var(g_minishell.envp, "_");
	if (!el)
		set_env_var(&g_minishell.envp, "_", argv[0]);
}

void	minishell(int argc, char **argv, char **envp)
{
	char		*cache[2];

	(void)argc;
	g_minishell.envp = NULL;
	g_minishell.envp = parse_array_to_env(envp, g_minishell.envp);
	init_env(argv);
	// signal(SIGINT, handle_signal);
	// signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cache[0] = get_promt(
				get_env_var(g_minishell.envp, "USER"),
				get_env_var(g_minishell.envp, "PWD"),
				get_env_var(g_minishell.envp, "HOME"));
		cache[1] = catch_tty(cache[0]);
		if (cache[1] == NULL)
			break ;
		free(cache[0]);
		// if (if_chars(cache[1]))
		// 	add_history(cache[1]);
		if (cache[1] != NULL)
			parse_input(cache[1]);
		free (cache[1]);
	}
}
