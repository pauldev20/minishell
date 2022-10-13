/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/13 12:33:43 by mhedtman         ###   ########.fr       */
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

char	*get_cmd_array(char **cmd_array, char **token_array, int start, int stop)
{
	char	*cmd_args;
	
	cmd_args = ft_strdup("");
	while (start < stop)
	{
		if (str_is_equal(token_array[start], "WORD"))
		{
			if (cmd_args[0] == '\0')
				cmd_args = ft_strjoin(cmd_args, cmd_array[start]);
			else
			{
				cmd_args = ft_strjoin(cmd_args, " ");
				cmd_args = ft_strjoin(cmd_args, cmd_array[start]);
			}
		}
		start++;
	}
	return (cmd_args);
}

char	*get_infile(char **cmd_array, char **token_array, int start, int stop)
{
	char	*infile;
	
	infile = NULL;
	while (start < stop)
	{
		if (str_is_equal(token_array[start], "INFILE"))
			infile = ft_strdup(cmd_array[start]);
		start++;
	}
	return (infile);
}

t_execute_table	*get_execute_table(char **token_array, char **cmd_array)
{
	int	stop;
	int	start;
	int	i;
	t_execute_table	*execute_table;

	// print_arr(token_array);
	execute_table = (t_execute_table *)malloc(sizeof(t_execute_table));
	execute_table->cmd_array = (char **)ft_calloc((get_pipe_amount(token_array) + 1), sizeof(char *));
	execute_table->infiles =  (char **)ft_calloc((get_pipe_amount(token_array) + 1), sizeof(char *));
	execute_table->outfiles =  (char **)ft_calloc((get_pipe_amount(token_array) + 1), sizeof(char *));
	start = 0;
	stop = 0;
	i = 0;
	while (token_array[stop] != NULL)
	{
		if (str_is_equal(token_array[stop], "PIPE"))
		{
			execute_table->cmd_array[i] = get_cmd_array(cmd_array, token_array, start, stop);
			execute_table->infiles[i] = get_infile(cmd_array, token_array, start, stop);
			printf("EXECUTE[%d]: CMD[%s] INFILE [%s]\n", i, execute_table->cmd_array[i], execute_table->infiles[i]);
			// execute_table->outfiles[i] = get_outfile(cmd_array, token_array, start, stop);
			i++;
			start = stop;
		}
		stop++;
	}
	execute_table->cmd_array[i] = get_cmd_array(cmd_array, token_array, start, stop);
	execute_table->infiles[i] = get_infile(cmd_array, token_array, start, stop);
	// printf("CMD AND ARGS[%d]: %s\n", i, execute_table->cmd_array[i]);
	return (execute_table);
}

void	execute_pipeline(t_execute_table *execute_table)
{
	(void)execute_table;
}
// void	execute_pipeline(char **cmd_array, char **token_array)
// {
// 	int		i;
// 	int		io_modifier[2];
// 	int		start_stop[2];
// 	char	**env;
	

// 	env = get_env_arr(g_minishell.envp);
// 	start_stop[0] = 0;
// 	start_stop[1] = 0;
// 	io_modifier[0] = get_infile_fd(token_array, cmd_array);
// 	io_modifier[1] = get_outfile_fd(token_array, cmd_array);
// 	cmd_array = delete_io(cmd_array, token_array, &io_modifier[0]);
// 	token_array = get_token_array(cmd_array);
// 	print_arr(cmd_array);
// 	dup2(io_modifier[0], STDIN_FILENO);
// 	i = -1;
// 	while (++i < get_pipe_amount(token_array))
// 	{
// 		start_stop[0] = get_start(token_array, start_stop[0], start_stop[1]);
// 		start_stop[1] = get_stop(token_array, start_stop[1], start_stop[0]);
// 		child_process(cmd_array, env, start_stop);
// 	}
// 	dup2(io_modifier[1], STDOUT_FILENO);
// 	start_stop[0] = get_start(token_array, start_stop[0], start_stop[1]);
// 	start_stop[1] = get_stop(token_array, start_stop[1], start_stop[0]);
// 	execute(cmd_array, env, start_stop);
// 	free_array(env);
// }

/*	"MAIN" RETURNS ERRORS ETC. */
int	start_execute(char **cmd_arr)
{
	pid_t			id;
	t_execute_table	*execute_table;
	char			**token_array;
	int 			status;

	g_minishell.executing = 1;
	id = fork();
	status = 0;
	if (id == 0)
	{
		cmd_arr = execute_prejobs(cmd_arr);
		token_array = get_token_array(cmd_arr);
		execute_table = get_execute_table(token_array, cmd_arr);
		execute_pipeline(execute_table);
	}
	else
	{
		waitpid(id, &status, 0);
		g_minishell.executing = 0;
		return ((status >> 8) & 0x000000ff);
	}
	return (0);
}
