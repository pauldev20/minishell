/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:07:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/22 17:38:42 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

static void	catch_output(int *stdoutcpy, int **stdout_pipe)
{
	*stdout_pipe = (int *)malloc(sizeof(int) * 2);
	*stdoutcpy = dup(STDOUT_FILENO);
	pipe(*stdout_pipe);
	dup2((*stdout_pipe)[1], STDOUT_FILENO);
}

static void	write_output(int *stdoutcpy, int **stdout_pipe)
{
	char	buf[1];
	int		chars;

	chars = 0;
	close((*stdout_pipe)[1]);
	dup2(*stdoutcpy, STDOUT_FILENO);
	while (read((*stdout_pipe)[0], buf, 1) > 0)
	{
		chars++;
		write(1, buf, 1);
	}
	if (chars && buf[0] != '\n')
		printf("%s%%%s\n", WHITE_BLACK, RESET);
	close((*stdout_pipe)[0]);
	free((*stdout_pipe));
}

static int	if_chars(char *str)
{
	int	chars;

	chars = 0;
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
	int			stdout_cpy;
	int			*stdout_pipe;

	(void)argc;
	g_minishell.envp = NULL;
	g_minishell.envp = parse_array_to_env(envp, g_minishell.envp);
	init_env(argv);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cache[0] = get_promt();
		cache[1] = readline(cache[0]);
		free(cache[0]);
		if (if_chars(cache[1]))
			add_history(cache[1]);
		catch_output(&stdout_cpy, &stdout_pipe);
		if (cache[1] != NULL)
			parse_input(cache[1]);
		write_output(&stdout_cpy, &stdout_pipe);
		free (cache[1]);
	}
}
