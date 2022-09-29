/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/09/29 17:06:57 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char **environ;
/* TO DO:
	- ADD ERROR HANDELING
*/

/*  RETURNS FD OF A FILE IN THE RIGHT MODE
 	[R_ONLY | WR_ONLY WITH APPEND OR TRUNC DEPENDING ON THE TYPE NEEDED] */

/*  CHECKS IF THE TOKEN PASSED AS AN ARG IS AN REDIRECTOR */
bool	is_input_redirector(char *str)
{
	if (ft_strnstr(str, "LESS", 4) || ft_strnstr(str, "DLESS", 5))
		return (true);
	return (false);
}

bool	is_output_redirector(char *str)
{
	if (ft_strnstr(str, "GREAT", 5) || ft_strnstr(str, "DGREAT", 6))
		return (true);
	return (false);
}

int	get_outfile_fd(char **token, char **arr)
{
	int	fd;
	int	i;
	
	fd = STDOUT_FILENO;
	i = -1;
	while (token[++i] != NULL)
	{
		if (is_output_redirector(token[i]))
		{
			if (ft_strnstr(token[i], "GREAT", 5))
				fd = open(arr[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 00700);
			else if (ft_strnstr(token[i], "DGREAT", 6))
				fd = open(arr[i + 1], O_WRONLY | O_CREAT | O_APPEND, 00700);
		}
	}
	return (fd);
}

void	here_doc(char *limiter)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return ;
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_terminal_line(fd[1]) != NULL)
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	get_infile_fd(char **token, char **arr)
{
	int	fd;
	int	i;
	
	fd = STDIN_FILENO;
	i = -1;
	while (token[++i] != NULL)
	{
		if (is_input_redirector(token[i]))
		{
			if (ft_strnstr(token[i], "LESS", 4))
				fd = open(arr[i + 1], O_RDONLY, 0777);
			else if (ft_strnstr(token[i], "DLESS", 5))
				here_doc(arr[i + 1]);
		}
	}
	return (fd);
}

/*	JOINS '>' + '>' AND '<' + '<' IF NEEDED */
char	**join_io_modifier(char **arr)
{
	int	old_i;
	int new_i;
	
	old_i = 0;
	new_i = 0;
	while (arr[old_i] != NULL)
	{
		if (arr[old_i + 1] != NULL)
		{
			if (arr[old_i][0] == '<' && arr[old_i + 1][0] == '<')
			{
				arr[new_i] = ft_strjoin(arr[new_i], "<");
				old_i++;
			}
			else if (arr[old_i][0] == '>' && arr[old_i + 1][0] == '>')
			{
				arr[new_i] = ft_strjoin(arr[new_i], ">");
				old_i++;
			}
			else
				arr[new_i] = arr[old_i];
		}
		else
			arr[new_i] = arr[old_i];
		new_i++;
		old_i++;
	}
	while (new_i < old_i)
	{
		arr[new_i] = NULL;
		new_i++;
	}
	arr[new_i] = NULL;
	return (arr);
}

/*  RETURNS THE AMOUNT OF PIPES TO CHECK HOW MANY CMDS
	WILL BE ADDED TO PIPEX */ 
int		get_pipe_amount(char **tokens)
{
	int	pipe_counter;
	int	i;

	pipe_counter = 0;
	i = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strnstr(tokens[i], "PIPE", 4))
			pipe_counter++;
		i++;
	}
	return (pipe_counter);
}

/*  CREATES A TOKEN LIST TO KNOW WHAT WE ARE WORKING
	WITH [PIPES | REDIRECTOR | WORDS] */
char	**get_token_array(char **arr)
{
	char	**tokens;
	int		i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	tokens = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i][0] == '|')
			tokens[i] = ft_strdup("PIPE");
		else if (arr[i][0] == '<')
		{
			if (arr[i][1] == '<')
				tokens[i] = ft_strdup("DLESS");
			else
				tokens[i] = ft_strdup("LESS");
		}
		else if (arr[i][0] == '>')
		{
			if (arr[i][1] == '>')
				tokens[i] = ft_strdup("DGREAT");
			else
				tokens[i] = ft_strdup("GREAT");
		}
		else
			tokens[i] = ft_strdup("WORD");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

/*  DELETES THE REDIRECTORS OUT OF THE STRING SO THAT 
	ONLY THE CMD PIPELINES REMAINS AND WE CAN ITERATE OVER IT */
char	**delete_io(char **arr, char **tokens)
{
	int		i;
	int		new_i;

	new_i = 0;
	i = 0;
	while (tokens[i] != NULL)
	{
		if (is_input_redirector(tokens[i]) || is_output_redirector(tokens[i]))
			i += 2;
		arr[new_i] = arr[i];
		if (arr[new_i] == NULL)
			break ;
		new_i++;
		i++;
	}
	while (new_i < i)
	{
		arr[new_i] = NULL;
		new_i++;
	}
	return (arr);
}

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
				|| !ft_strnstr(tokens[i - 1], "WORD", 4) || !ft_strnstr(tokens[i + 1], "WORD", 4))
			{
				printf("minishell: syntax error near pipe\n");
				return (false);
			}
		}
		else if (is_input_redirector(tokens[i]) || is_output_redirector(tokens[i]))
		{
			if (tokens[i + 1] == NULL || !ft_strnstr(tokens[i + 1], "WORD", 4))
			{
				printf("minishell: syntax error near io-modifier\n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

int	get_start(char	**tokens, int start, int stop)
{
	if (ft_strnstr(tokens[stop], "GREAT", 5) || ft_strnstr(tokens[stop], "DGREAT", 6)
		|| ft_strnstr(tokens[stop], "LESS", 4) || ft_strnstr(tokens[stop], "DLESS", 5 ))
		start = stop + 2;
	else if (stop != 0)
		start = stop + 1;
	return (start);
}

int	get_stop(char **tokens, int stop, int start)
{
	stop = start;
	if (stop != 0)
		stop++;
	while (tokens[stop] != NULL && !ft_strnstr(tokens[stop], "PIPE", 4) 
		&& !ft_strnstr(tokens[stop], "GREAT", 5) && !ft_strnstr(tokens[stop], "DGREAT", 6)
		&& !ft_strnstr(tokens[stop], "LESS", 4) && !ft_strnstr(tokens[stop], "DLESS", 5 ))
		stop++;
	return (stop);
}

bool	modify_io(char **cmd_array, int mode)
{
	int		i;
	char	**tokens;
	int	io_modifier;
	
	cmd_array = join_io_modifier(cmd_array);
	tokens = get_token_array(cmd_array);
	if (!check_syntax(tokens))
		return (false);
	i = 0;
	while (tokens[i] != NULL)
	{
		if (mode == INFILE_MODE)
		{
			io_modifier = STDIN_FILENO;
			if (is_input_redirector(tokens[i]))
			{
				if (ft_strnstr(tokens[i], "LESS", 4))
					io_modifier = open(cmd_array[i + 1], O_RDONLY, 0777);
				else if (ft_strnstr(tokens[i], "DLESS", 5))
					here_doc(cmd_array[i + 1]);
				dup2(io_modifier, STDIN_FILENO);
			}
		}
		else if (mode == OUTFILE_MODE)
		{
			io_modifier = STDOUT_FILENO;
			if (is_output_redirector(tokens[i]))
			{
				if (ft_strnstr(tokens[i], "GREAT", 5))
					io_modifier = open(cmd_array[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 00700);
				else if (ft_strnstr(tokens[i], "DGREAT", 6))
					io_modifier = open(cmd_array[i + 1], O_WRONLY | O_CREAT | O_APPEND, 00700);
				dup2(io_modifier, STDOUT_FILENO);
			}
		}
		i++;
	}
	return (true);
}

/*	CHANGES INFILE IF NEEDED AND GOES INTO PIPEX 
	MAYBE ALSO NEEDS TO CHANGE OUTFILE AND EXECUTE LAST CMD */
void	execute_pipeline(char **cmd_array)
{
	char	**token_array;
	int		i;
	int		start_stop[2];

	start_stop[0] = 0;
	start_stop[1] = 0;
	if (!modify_io(cmd_array, INFILE_MODE))
		return ;
	i = 0;
	token_array = get_token_array(cmd_array);
	while (i < get_pipe_amount(token_array))
	{
		start_stop[0] = get_start(token_array, start_stop[0], start_stop[1]);
		start_stop[1] = get_stop(token_array, start_stop[1], start_stop[0]);
		child_process(cmd_array, environ, start_stop);
		i++;
	}
	if (!modify_io(cmd_array, OUTFILE_MODE))
		return ;
	start_stop[0] = get_start(token_array, start_stop[0], start_stop[1]);
	start_stop[1] = get_stop(token_array, start_stop[1], start_stop[0]);
	printf("%s	%s %d %d\n", cmd_array[start_stop[0]], cmd_array[start_stop[1]], start_stop[0], start_stop[1]);
	execute(cmd_array, environ, start_stop);
}


// OLD
// void	execute_pipeline(char **cmd_array)
// {
// 	char	**token_array;
// 	int		i;
// 	int		io_modifier[2];
// 	int		start_stop[2];

// 	// -> pre jobs
// 	start_stop[0] = 0;
// 	start_stop[1] = 0;
// 	cmd_array = join_io_modifier(cmd_array);
// 	token_array = get_token_array(cmd_array);
// 	if (!check_syntax(token_array))
// 		return ;
// 	io_modifier[0] = get_infile_fd(token_array, cmd_array);
// 	io_modifier[1] = get_outfile_fd(token_array, cmd_array);
// 	// -> executer
// 	dup2(io_modifier[0], STDIN_FILENO);
// 	i = 0;
// 	while (i < get_pipe_amount(token_array))
// 	{
// 		start_stop[0] = get_start(token_array, start_stop[0], start_stop[1]);
// 		start_stop[1] = get_stop(token_array, start_stop[1], start_stop[0]);
// 		child_process(cmd_array, environ, start_stop);
// 		i++;
// 	}
// 	dup2(io_modifier[1], STDOUT_FILENO);
// 	start_stop[0] = get_start(token_array, start_stop[0], start_stop[1]);
// 	start_stop[1] = get_stop(token_array, start_stop[1], start_stop[0]);
// 	execute(cmd_array, environ, start_stop);
// }

/*	"MAIN" RETURNS ERRORS ETC. */
int	start_execute(char **arr)
{
	pid_t	id;

	id = fork();
	if (id == 0)
		execute_pipeline(arr);
	wait(&id);
	return (0);
}
