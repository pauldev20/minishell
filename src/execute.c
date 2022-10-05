/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/05 16:34:11 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

/* CHECKS FOR GRAMMAR MISTAKES IN THE SYNTAX*/
bool	check_syntax(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strnstr(tokens[i], "PIPE", 4))
		{
			if (tokens[i - 1] == NULL || tokens[i + 1] == NULL
				|| !ft_strnstr(tokens[i - 1], "WORD", 4)
				|| !ft_strnstr(tokens[i + 1], "WORD", 4))
			{
				printf("\033[31mminishell: syntax error near pipe\n");
				return (false);
			}
		}
		else if (is_input_redirector(tokens[i])
			|| is_output_redirector(tokens[i]))
		{
			if (tokens[i + 1] == NULL || !ft_strnstr(tokens[i + 1], "WORD", 4))
			{
				printf("\033[31mminishell: syntax error near io-modifier\n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

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

/*	CHANGES INFILE IF NEEDED AND GOES INTO PIPEX 
	MAYBE ALSO NEEDS TO CHANGE OUTFILE AND EXECUTE LAST CMD */
void	execute_pipeline(char **cmd_array)
{
	char	**token_array;
	int		i;
	int		io_modifier[2];
	int		start_stop[2];

	start_stop[0] = 0;
	start_stop[1] = 0;
	cmd_array = join_io_modifier(cmd_array);
	token_array = get_token_array(cmd_array);
	if (!check_syntax(token_array))
		return ;
	io_modifier[0] = get_infile_fd(token_array, cmd_array);
	io_modifier[1] = get_outfile_fd(token_array, cmd_array);
	cmd_array = delete_io(cmd_array, token_array);
	token_array = get_token_array(cmd_array);
	dup2(io_modifier[0], STDIN_FILENO);
	i = 0;
	while (i < get_pipe_amount(token_array))
	{
		start_stop[0] = get_start(token_array, start_stop[0], start_stop[1]);
		start_stop[1] = get_stop(token_array, start_stop[1], start_stop[0]);
		child_process(cmd_array, environ, start_stop);
		i++;
	}
	dup2(io_modifier[1], STDOUT_FILENO);
	start_stop[0] = get_start(token_array, start_stop[0], start_stop[1]);
	start_stop[1] = get_stop(token_array, start_stop[1], start_stop[0]);
	execute(cmd_array, environ, start_stop);
}

/*	"MAIN" RETURNS ERRORS ETC. */
int	start_execute(char **arr)
{
	pid_t	id;
	int		i;

	id = fork();
	if (id == 0)
	{
		execute_pipeline(arr);
		i = 0;
		while (arr[i])
		{
			if (ft_strnstr(arr[i], "exit", 5))
				exit(id);
			i++;
		}
		return (-1);
	}
	else
	{
		wait(&id);
		return (0);
	}
}
