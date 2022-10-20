/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:07:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/21 01:01:00 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO DO:
	- HANDLE "< > + FILE" = ERROR AND "<> + FILE" NO ERROR | P
	- in heredoc when ^D no output + leaks | P
	- "<<" eof what should happen? -> cmd not found
	- "< <" eof what should happen? -> cmd not found
	- echo " \ " |  wenn man "echo \" -> nur ein space wenn "echo \test" \ wird gelöscht und und es displayed nur test
	- parser darf ""

	________________________________________________________________________
	FÜR DAS EVAL SHEET FEHLT:
	- TABS ODER SPACES ALS INPUT GEBEN IMMER EINEN PARSER ERROR - 🔮 ----> Fixed, tabs konnte ich nicht testen
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

int	minishell(int argc, char **argv, char **envp)
{
	char	*cache[2];
	char	**cmd_array;
	int		ret;

	ret = 1;
	(void)argc;
	g_minishell.envp = NULL;
	g_minishell.envp = parse_array_to_env(envp, g_minishell.envp);
	g_minishell.executing = 0;
	g_minishell.sigint = 0;
	init_env(argv);
	signal(SIGINT, handle_signal);
	// signal quit!!!!
	while (1)
	{
		cache[0] = get_prompt(
				get_env_var(g_minishell.envp, "USER"),
				get_env_var(g_minishell.envp, "PWD"),
				get_env_var(g_minishell.envp, "HOME"),
				g_minishell.exit_code);
		g_minishell.sigint = 0;
		cache[1] = catch_tty(cache[0]);
		if (cache[1] == NULL)
			break ;
		free(cache[0]);
		if (cache[1] != NULL)
			cmd_array = parse_input(cache[1]);
		if (cmd_array && cmd_array[0])
			ret = start_execute(cmd_array);
		free_array(cmd_array);
		free (cache[1]);
	}
	return (ret);
}
