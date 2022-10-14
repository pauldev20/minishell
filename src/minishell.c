/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:07:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/14 13:41:50 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO DO:
	- handle spaces between [" "] echo "hi " -> more spaces should be deleted"
	- CATCH ^C AND ^\ | 🔮
	- HANDLE QUOTATION TO PARSER | 🔮
	- CHECK IF "> > || < <" OR "<< | >>" ALREADY THROW ERROR IN PARSER IF THE FIRST HAPPENED | P
	- HANDLE "< > + FILE" = ERROR AND "<> + FILE" NO ERROR | P
	- REPLACE CHAR **ENVIRON IN EXECUTE.C (HOW TO HANDLE ENVP LIST OR ARRAY?) | 🔮
	- FIX UNSET | 🔮
	- in heredoc when ^C quit whole thing | 🔮
	- in heredoc when ^D no output + leaks | P
	- ADD $? | M
	- SET ERROR STATUS AND EXIT CODES | M
	- leaks | M
	- ADD ERROR HANDELING IN EXECVE | ✅
	- echo | cat -e -> gives ^@$ should give $ | ✅
	- cat /dev/urandom | ls | ✅
	- chmod 000 -> check for permissions | ✅ 
	- in heredoc << eof cat -> also stops on "eof " (with space) | ✅ 
	- only cd should go into home directory | ✅
	- global error code | NEW | 
	- fix start_execute forking | NEW | 🔮
	- call correct exit | NEW | 
	- free arr_correctly | NEW | 🔮
	- change concept of start_execute !!! (env wont work if functions are called inside fork)
	- LEAKS?? WHERE? | NEW |
	- MORE SPACES BEFORE IO MODIFICATION 
	- echo hi | exit -> shoudl exit the pipe and not the programm
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
	// signal(SIGQUIT, SIG_IGN);
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
