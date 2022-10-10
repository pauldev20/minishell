/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/11 00:22:33 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_start(char	**tokens, int start, int stop)
{
	if (stop != 0)
		start = stop + 1;
	return (start);
}

int	get_stop(char **tokens, int stop, int start)
{
	if (stop != 0)
		stop++;
	while (tokens[stop] != NULL && ft_strnstr(tokens[stop], "PIPE", 4) == NULL)
		stop++;
	return (stop);
}

int	execute_process(char **cmd_array, char **token_array, int start_stop[2])
{
	
}
/*	CHANGES INFILE IF NEEDED AND GOES INTO PIPEX 
	MAYBE ALSO NEEDS TO CHANGE OUTFILE AND EXECUTE LAST CMD 
	
	NEED TO ADD A INFILE REDIRECTION IN EVERY COMMAND AND ARG FAMILY
	ONLY TAKES LAST IN AND OUTFILE OF THE FAMILY 
	IF THERE IS NO INPUT REDIRECTON !!AFTER!! A PIPE IT TAKES AN EMTPY
	FILE AS AN INPUT
	-> GET START STOP OF CMD + ARGS + REDIRECTIONS
	-> CHANGE FDs
	-> DELETE REDIRECTIONS
	-> EXECUTE*/

void	execute_pipeline(char **cmd_array, char **token_array)
{
	int		i;
	int		io_modifier[2];
	int		start_stop[2];
	char	**env;

	env = get_env_arr(g_minishell.envp);
	start_stop[0] = 0;
	start_stop[1] = 0;
	io_modifier[0] = get_infile_fd(token_array, cmd_array);
	io_modifier[1] = get_outfile_fd(token_array, cmd_array);
	cmd_array = delete_io(cmd_array, token_array, &io_modifier[0]);
	token_array = get_token_array(cmd_array);
	print_arr(cmd_array);
	dup2(io_modifier[0], STDIN_FILENO);
	i = -1;
	while (++i < get_pipe_amount(token_array))
	{
		start_stop[0] = get_start(token_array, start_stop[0], start_stop[1]);
		start_stop[1] = get_stop(token_array, start_stop[1], start_stop[0]);
		child_process(cmd_array, env, start_stop);
	}
	dup2(io_modifier[1], STDOUT_FILENO);
	start_stop[0] = get_start(token_array, start_stop[0], start_stop[1]);
	start_stop[1] = get_stop(token_array, start_stop[1], start_stop[0]);
	execute(cmd_array, env, start_stop);
	free_array(env);
}

/*	"MAIN" RETURNS ERRORS ETC. */
int	start_execute(char **cmd_arr)
{
	pid_t	id;
	int		i;
	char	**token_array;
	int 	status;

	g_minishell.executing = 1;
	id = fork();
	status = 0;
	if (id == 0)
	{
		cmd_arr = execute_prejobs(cmd_arr);
		token_array = get_token_array(cmd_arr);
		execute_pipeline(cmd_arr, token_array);
		i = 0;
		while (cmd_arr[i])
		{
			if (str_is_equal(cmd_arr[i], "exit"))
				exit(id); // correct exit????
			i++;
		}
		exit(127);
	}
	else
	{
		waitpid(id, &status, 0);
		g_minishell.executing = 0;
		return ((status >> 8) & 0x000000ff);
	}
}
