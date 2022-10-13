/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/13 15:07:15 by mhedtman         ###   ########.fr       */
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

char	*get_outfile(char **cmd_array, char **token_array, int start, int stop)
{
	char	*outfile;
	
	outfile = NULL;
	while (start < stop)
	{
		if (str_is_equal(token_array[start], "OUTFILE"))
			outfile = ft_strdup(cmd_array[start]);
		start++;
	}
	return (outfile);
}

char	*get_infile_type(char **cmd_array, char **token_array, int start, int stop)
{
	char	*infile;
	
	infile = NULL;
	while (start < stop)
	{
		if (str_is_equal(token_array[start], "DLESS"))
			infile = ft_strdup("DLESS");
		else if (str_is_equal(token_array[start], "LESS"))
			infile = ft_strdup("LESS");
		start++;
	}
	return (infile);
}

char	*get_outfile_type(char **cmd_array, char **token_array, int start, int stop)
{
		char	*outfile;
	
	outfile = NULL;
	while (start < stop)
	{
		if (str_is_equal(token_array[start], "GREAT"))
			outfile = ft_strdup("GREAT");
		else if (str_is_equal(token_array[start], "DGREAT"))
			outfile = ft_strdup("DGREAT");
		start++;
	}
	return (outfile);
}

t_execute_table	*memory_allocation_arrays(t_execute_table *execute_table, char **token_array)
{
	execute_table->cmd_array = (char **)ft_calloc((get_pipe_amount(token_array) + 1), sizeof(char *));
	execute_table->infiles =  (char **)ft_calloc((get_pipe_amount(token_array) + 1), sizeof(char *));
	execute_table->infile_type = (char **)ft_calloc((get_pipe_amount(token_array) + 1), sizeof(char *));
	execute_table->outfiles =  (char **)ft_calloc((get_pipe_amount(token_array) + 1), sizeof(char *));
	execute_table->outfile_type = (char **)ft_calloc((get_pipe_amount(token_array) + 1), sizeof(char *));
	return (execute_table);
}

t_execute_table	*get_execute_table(char **token_array, char **cmd_array)
{
	t_execute_table	*execute_table;
	int	stop;
	int	start;
	int	i;

	execute_table = (t_execute_table *)malloc(sizeof(t_execute_table));
	execute_table = memory_allocation_arrays(execute_table, token_array);
	start = 0;
	stop = 0;
	i = 0;
	while (token_array[stop] != NULL)
	{
		if (str_is_equal(token_array[stop], "PIPE"))
		{
			execute_table->cmd_array[i] = get_cmd_array(cmd_array, token_array, start, stop);
			execute_table->infiles[i] = get_infile(cmd_array, token_array, start, stop);
			execute_table->infile_type[i] = get_infile_type(cmd_array, token_array, start, stop);
			execute_table->outfiles[i] = get_outfile(cmd_array, token_array, start, stop);
			execute_table->outfile_type[i] = get_outfile_type(cmd_array, token_array, start, stop);
			// printf("NUMBER[%d]\nCMD [%s], IN [%s], OUT[%s]\n\tIN_T [%s] OUT_T [%s]\n", i, execute_table->cmd_array[i], execute_table->infiles[i], execute_table->outfiles[i], execute_table->infile_type[i], execute_table->outfile_type[i]);
			i++;
			start = stop;
		}
		stop++;
	}
	execute_table->cmd_array[i] = get_cmd_array(cmd_array, token_array, start, stop);
	execute_table->infiles[i] = get_infile(cmd_array, token_array, start, stop);
	execute_table->infile_type[i] = get_infile_type(cmd_array, token_array, start, stop);
	execute_table->outfiles[i] = get_outfile(cmd_array, token_array, start, stop);
	execute_table->outfile_type[i] = get_outfile_type(cmd_array, token_array, start, stop);
	// printf("NUMBER[%d]\nCMD [%s], IN [%s], OUT[%s]\n\tIN_T [%s] OUT_T [%s]\n", i, execute_table->cmd_array[i], execute_table->infiles[i], execute_table->outfiles[i], execute_table->infile_type[i], execute_table->outfile_type[i]);
	return (execute_table);
}

void	execute_pipeline(t_execute_table *execute_table, char **token_array)
{
	int	io_modifier[2];
	int	i;
	int	max;
	char	**env;

	env = get_env_arr(g_minishell.envp);
	i = 0;
	io_modifier[0] = get_infile_fd(execute_table->infile_type[i], execute_table->infiles[i], STDIN_FILENO);
	dup2(io_modifier[0], STDIN_FILENO);
	i = -1;
	while (++i < get_pipe_amount(token_array))
	{
		child_process(execute_table, env, i);
	}
	io_modifier[1] = get_outfile_fd(execute_table->outfile_type[i], execute_table->outfiles[i], STDOUT_FILENO);
	dup2(io_modifier[1], STDOUT_FILENO);
	execute(ft_split(execute_table->cmd_array[i], ' '), env);
}

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
		if (!cmd_arr)
			exit(258);
		token_array = get_token_array(cmd_arr);
		execute_table = get_execute_table(token_array, cmd_arr);
		execute_pipeline(execute_table, token_array);
	}
	else
	{
		waitpid(id, &status, 0);
		g_minishell.executing = 0;
		return ((status >> 8) & 0x000000ff);
	}
	return (0);
}
