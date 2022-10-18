/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/18 16:36:47 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipeline(t_ct *exetable, char **token_array)
{
	int		io_modifier[2];
	int		i;
	char	**env;

	env = get_env_arr(g_minishell.envp);
	i = 0;
	io_modifier[0] = get_infile_fd(exetable, exetable->in_type[i],
			exetable->in[i], 0);
	dup2(io_modifier[0], STDIN_FILENO);
	while (i < get_pipe_amount(token_array))
	{
		child_process(exetable, env, i);
		i++;
	}
	io_modifier[1] = get_outfile_fd(exetable->out_type[i],
			exetable->out[i], 1);
	dup2(io_modifier[1], STDOUT_FILENO);
	return (execute(ft_split(exetable->cmd_array[i], ' '), env));
}

/*	"MAIN" RETURNS ERRORS ETC. */
char	**check_for_builtins(char **cmds)
{
	int	i;
	int	offset;
	int	len;

	offset = 0;
	i = 0;
	len = 0;
	while (cmds[len] != NULL)
		len++;
	while (cmds[i] != NULL)
	{
		if (str_is_equal(cmds[i], "unset") || str_is_equal(cmds[i], "export"))
		{
			builtin_parser(cmds + i, 2, 0);
			offset += 2;
		}
		cmds[i] = cmds[i + offset];
		i++;
	}
	while (i < len)
	{
		cmds[i] = NULL;
		i++;
	}
	return (cmds);
}

int	start_execute(char **cmd_arr)
{
	pid_t			id;
	t_ct			*cmd_table;
	char			**token_array;
	int				status;

	g_minishell.executing = 1;
	cmd_arr = check_for_builtins(cmd_arr);
	id = fork();
	status = 0;
	if (id == 0)
	{
		cmd_arr = execute_prejobs(cmd_arr);
		token_array = get_token_array(cmd_arr);
		cmd_table = get_cmd_table(token_array, cmd_arr);
		execute_pipeline(cmd_table, token_array);
	}
	else
	{
		waitpid(id, &status, 0);
		g_minishell.executing = 0;
		g_minishell.exit_code = (status >> 8) & 0x000000ff;
		return ((status >> 8) & 0x000000ff);
	}
	return (EXIT_SUCCESS);
}
