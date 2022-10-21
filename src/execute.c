/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/21 15:15:21 by mhedtman         ###   ########.fr       */
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
	free_array(token_array);
	return (execute(exetable->cmd_array[i], exetable->arg_array[i], env));
}

char	**check_for_builtins(char **cmds)
{
	int	i;
	int	offset;

	offset = 0;
	i = 0;
	cmds = catch_builtins(cmds, &i, &offset);
	if (cmds == NULL || cmds[0] == NULL)
		return (empty_arr());
	if (cmds[i - offset] != NULL && cmds[i - offset][0] == '|')
		cmds[i - offset] = NULL;
	while (i < array_len(cmds))
	{
		cmds[i] = NULL;
		i++;
	}
	return (cmds);
}

void	child_executer(char	**cmd_arr)
{
	t_ct			*cmd_table;

	if (!cmd_arr)
		print_error(QUOTE, NULL, 1);
	if (cmd_arr[0][0] == '\0')
		print_error(EXECUTE_ERROR, NULL, 127);
	cmd_arr = execute_prejobs(cmd_arr);
	cmd_table = get_cmd_table(get_token_array(cmd_arr), cmd_arr);
	execute_pipeline(cmd_table, get_token_array(cmd_arr));
	free_array(cmd_arr);
	free_cmd_table(cmd_table);
}

int	start_execute(char **cmd_arr)
{
	pid_t			id;
	int				status;

	g_minishell.executing = 1;
	if (cmd_arr)
		cmd_arr = check_for_builtins(cmd_arr);
	id = fork();
	status = 0;
	if (id == 0)
		child_executer(cmd_arr);
	else
	{
		waitpid(id, &status, 0);
		free_array(cmd_arr);
		g_minishell.executing = 0;
		g_minishell.exit_code = (status >> 8) & 0x000000ff;
		return ((status >> 8) & 0x000000ff);
	}
	return (EXIT_SUCCESS);
}
