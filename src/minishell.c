/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:07:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/24 01:32:37 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd not working: cd ~/Desktop
// echo -nnnnn hihias asldjkasldjkasjde jklae -n -> echo -nnnn-n hihias asldjkasldjkasjde jklae -n
// export TEST = 3: no errors
// errors if too many arguments??
// env -i ./minishell: text compleatly red ?
// echo \i get not removed?

// bei unset und export leaks
// free everything correctly on exit
// echo $? -> 2 memory leaks per call
// heredoc leaks extremly

static void	init_env(char **argv)
{
	char	*str;
	t_env	*el;

	el = get_env_var(g_minishell.envp, "SHLVL");
	if (!el)
		set_env_var(&g_minishell.envp, "SHLVL", "1");
	else
	{
		str = ft_itoa(ft_atoi(el->value) + 1);
		set_env_var(&g_minishell.envp, "SHLVL", str);
		free(str);
	}
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

static void	init_minishell(char **envp, char **argv)
{
	g_minishell.envp = NULL;
	g_minishell.envp = parse_array_to_env(envp, g_minishell.envp);
	g_minishell.executing = 0;
	g_minishell.sigint = 0;
	init_env(argv);
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
	init_minishell(envp, argv);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		g_minishell.sigint = 0;
		g_minishell.pid = -1;
		cache[1] = catch_tty(get_quick_prompt());
		if (cache[1] == NULL)
			break ;
		cmd_array = parse_input(cache[1]);
		ret = check_pipe_error(cache[1]);
		if (cmd_array && cmd_array[0])
			ret = start_execute(&cmd_array);
		else if (!cmd_array)
			print_error(QUOTE, NULL, -1);
		free_array(cmd_array);
		free (cache[1]);
	}
	return (ret);
}
