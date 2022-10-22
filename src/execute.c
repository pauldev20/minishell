/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/22 22:22:57 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipeline(t_ct *exetable, char **token_array)
{
	int		io_modifier[2];
	int		i;
	char	**env;
	int		pipes;

	pipes = get_pipe_amount(token_array);
	env = get_env_arr(g_minishell.envp);
	i = 0;
	io_modifier[0] = get_infile_fd(exetable, exetable->in_type[i],
			exetable->in[i], 0);
	dup2(io_modifier[0], STDIN_FILENO);
	while (i < pipes)
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
	{
		if (cmds)
			free(cmds);
		return (empty_arr());
	}
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
	if (cmd_arr)
		free_array(cmd_arr);
	if (cmd_table)
		free_cmd_table(cmd_table);
}

char	**handle_here_docs(char **cmd_arr)
{
	char		**here_docs;
	char		**tokens;

	cmd_arr = join_io_modifier(cmd_arr);
	tokens = get_token_array(cmd_arr);
	if (!check_pre_syntax(tokens))
	{
		free_array(tokens);
		return (cmd_arr);
	}
	free_array(tokens);
	here_docs = get_here_doc_limiters(cmd_arr);
	if (here_docs[0] != NULL)
		here_doc_execute(here_docs);
	free_array(here_docs);
	return (cmd_arr);
}

int	start_execute(char ***cmd_arr)
{
	int		status;

	status = 0;
	g_minishell.executing = 1;
	if (*cmd_arr)
	{
		*cmd_arr = check_for_builtins(*cmd_arr);
		*cmd_arr = handle_here_docs(*cmd_arr);
	}
	if (!g_minishell.sigint)
	{
		g_minishell.pid = fork();
		if (g_minishell.pid == 0)
			child_executer(*cmd_arr);
		else
		{
			waitpid(g_minishell.pid, &status, 0);
			g_minishell.executing = 0;
			g_minishell.exit_code = (status >> 8) & 0x000000ff;
			return ((status >> 8) & 0x000000ff);
		}
	}
	g_minishell.executing = 0;
	return (EXIT_SUCCESS);
}
