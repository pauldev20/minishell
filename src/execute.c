/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/14 16:13:17 by mhedtman         ###   ########.fr       */
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
	int	 	create;
	outfile = NULL;
	while (start < stop)
	{
		if (str_is_equal(token_array[start], "OUTFILE"))
		{
			create = open(cmd_array[start], O_WRONLY | O_CREAT | O_TRUNC, 00700);
			outfile = ft_strdup(cmd_array[start]);
			close(create);
		}
		else if (str_is_equal(token_array[start], "WEIRDFILE"))
		{
			create = open(cmd_array[start], O_WRONLY | O_CREAT | O_TRUNC, 00700);
			close(create);	
		}
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
	execute_table->here_docs = (char **)ft_calloc((get_pipe_amount(token_array) + 1), sizeof(char *));
	execute_table->outfiles =  (char **)ft_calloc((get_pipe_amount(token_array) + 1), sizeof(char *));
	execute_table->outfile_type = (char **)ft_calloc((get_pipe_amount(token_array) + 1), sizeof(char *));
	return (execute_table);
}

t_execute_table *init_execute_table(t_execute_table *execute_table, char **cmd_array, int start, int stop, int i)
{
	char	**token_array;

	token_array = get_token_array(cmd_array);
	execute_table->cmd_array[i] = get_cmd_array(cmd_array, token_array, start, stop);
	execute_table->infiles[i] = get_infile(cmd_array, token_array, start, stop);
	execute_table->infile_type[i] = get_infile_type(cmd_array, token_array, start, stop);
	execute_table->outfiles[i] = get_outfile(cmd_array, token_array, start, stop);
	execute_table->outfile_type[i] = get_outfile_type(cmd_array, token_array, start, stop);
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
			execute_table = init_execute_table(execute_table, cmd_array, start, stop, i);
			i++;
			start = stop;
		}
		stop++;
	}
	execute_table->here_docs = get_here_doc_limiters(cmd_array);
	execute_table = init_execute_table(execute_table, cmd_array, start, stop, i);
	return (execute_table);
}

int	execute_pipeline(t_execute_table *execute_table, char **token_array)
{
	int	io_modifier[2];
	int	i;
	char	**env;

	env = get_env_arr(g_minishell.envp);
	i = 0;
	io_modifier[0] = get_infile_fd(execute_table, execute_table->infile_type[i], execute_table->infiles[i], STDIN_FILENO);
	dup2(io_modifier[0], STDIN_FILENO);
	while (i < get_pipe_amount(token_array))
	{
		child_process(execute_table, env, i);
		i++;
	}
	io_modifier[1] = get_outfile_fd(execute_table->outfile_type[i], execute_table->outfiles[i], STDOUT_FILENO);
	dup2(io_modifier[1], STDOUT_FILENO);
	return (execute(ft_split(execute_table->cmd_array[i], ' '), env));
}

/*	"MAIN" RETURNS ERRORS ETC. */

char	**check_for_unset(char **cmd_array)
{
	int	i;
	int offset;
	int len;
	offset = 0;
	i = 0;
	len = 0;
	while (cmd_array[len] != NULL)
		len++;
	while (cmd_array[i] != NULL)
	{
		if (str_is_equal(cmd_array[i], "unset"))
		{
			builtin_parser(cmd_array + i, 2, 0);
			offset += 2;
		}
		cmd_array[i] = cmd_array[i + offset];
		i++;
	}
	printf("TEST\n");
	while (i < len)
	{
		cmd_array[i] = NULL;
		i++;
	}
	return (cmd_array);
	
}

int	start_execute(char **cmd_arr)
{
	pid_t			id;
	t_execute_table	*execute_table;
	char			**token_array;
	int 			status;

	g_minishell.executing = 1;
	print_arr(cmd_arr);
	cmd_arr = check_for_unset(cmd_arr);
	print_arr(cmd_arr);
	id = fork();
	status = 0;
	if (id == 0)
	{
		cmd_arr = execute_prejobs(cmd_arr);
		if (!cmd_arr)
			exit(2);
		if (cmd_arr[0] == NULL || cmd_arr[0][0] == '\0')
			exit(127);
		token_array = get_token_array(cmd_arr);
		execute_table = get_execute_table(token_array, cmd_arr);
		status = execute_pipeline(execute_table, token_array);
	}
	else
	{
		waitpid(id, &status, 0);
		g_minishell.executing = 0;
		return ((status >> 8) & 0x000000ff);
	}
	return (EXIT_SUCCESS);
}
