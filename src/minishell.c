/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:07:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/19 10:49:00 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO DO:
	- CHECK IF "> > || < <" OR "<< | >>" ALREADY THROW ERROR IN PARSER IF THE FIRST HAPPENED | P
	- SEE /tests/cmds/mand/1_builtins.sh line 28 to line 42
	- "echo -nnnnnn" or "echo -n -n -n -n -n -n" should be seen as one flag but "echo hello -n" shouldnt be handled as a flag | P
	- " \ " should not be displayed | P
	- HANDLE "< > + FILE" = ERROR AND "<> + FILE" NO ERROR | P
	- in heredoc when ^D no output + leaks | P
	- when ^C just display a new line and dont show ^C also | P
	- fix set path in finding ./ls or .ls | M

	________________________________________________________________________
	FÜR DAS EVAL SHEET FEHLT:
	- RICHTIGES HANDLING BEI QUOTES -> DER EXPANDER DELETED DIE QUOTES IMMER EGAL OB $ ODER NICHT
	- TABS ODER SPACES ALS INPUT GEBEN IMMER EINEN PARSER ERROR
	- "CAT" UND DANN ^C ZEIGT 2 MAL DIE PROMPT AN
	- EXPORT REPLACED KEINE VORHANDENEN ENVS SONDERN FÜGT NUR NEUE HINZU
	- WENN MAN IRGENDEINE VORHANDENE ENV-VARIABLE UNSETTET WIRD DIESE GELÖSCHT ABER ES FUNKTIONIEREN KEINE COMMANDS MEHR DANACH
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
	while (1)
	{
		cache[0] = get_prompt(
				get_env_var(g_minishell.envp, "USER"),
				get_env_var(g_minishell.envp, "PWD"),
				get_env_var(g_minishell.envp, "HOME"));
		g_minishell.sigint = 0;
		cache[1] = catch_tty(cache[0]);
		if (cache[1] == NULL)
			break ;
		free(cache[0]);
		if (cache[1] != NULL)
			cmd_array = parse_input(cache[1]);
		ret = start_execute(cmd_array);
		free_array(cmd_array);
		free (cache[1]);
	}
	return (ret);
}
