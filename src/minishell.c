/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:07:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/21 15:10:47 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO DO:
	- HANDLE "< > + FILE" = ERROR AND "<> + FILE" NO ERROR | P
	- in heredoc when ^D no output + leaks | P
	- echo " \ " |  wenn man "echo \" -> nur ein space wenn "echo \test" \ 
		wird gelöscht und und es displayed nur test
	________________________________________________________________________
	FÜR DAS EVAL SHEET FEHLT:
	- UNSET PWD
	- LEAKS
	*/

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

char	*get_quick_prompt(void)
{
	char	*prompt;

	prompt = get_prompt(
			get_env_var(g_minishell.envp, "USER"),
			get_env_var(g_minishell.envp, "PWD"),
			get_env_var(g_minishell.envp, "HOME"),
			g_minishell.exit_code);
	return (prompt);
}

int	minishell(char **argv, char **envp)
{
	char	*cache[2];
	char	**cmd_array;
	int		ret;

	ret = 1;
	g_minishell.envp = NULL;
	g_minishell.envp = parse_array_to_env(envp, g_minishell.envp);
	g_minishell.executing = 0;
	g_minishell.sigint = 0;
	init_env(argv);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_minishell.sigint = 0;
		cache[1] = catch_tty(get_quick_prompt());
		if (cache[1] == NULL)
			break ;
		cmd_array = parse_input(cache[1]);
		ret = check_pipe_error(cache[1]);
		if (cmd_array && cmd_array[0])
			ret = start_execute(cmd_array);
		free (cache[1]);
	}
	return (ret);
}
