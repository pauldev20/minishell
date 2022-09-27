/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/09/27 11:45:43 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* TO DO:
	- ADD ERROR HANDELING
	- ADD PIPEX IMPLEMENTATION
*/

/*  RETURNS FD OF A FILE IN THE RIGHT MODE
 	[R_ONLY | WR_ONLY WITH APPEND OR TRUNC DEPENDING ON THE TYPE NEEDED] */
int fd_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY, 00700);
	return (fd);
}

int	fd_outfile_append(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 00700);
	return(fd);
}

int fd_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 00700);
	return(fd);
}

int	redirect_input(char *file, char *token)
{
	if (ft_strnstr(token, "LESS", 4))
		return (fd_infile(file));
	else if (ft_strnstr(token, "DLESS", 5))
		return (-10);
	return (0);
	//make here_doc
}

int	redirect_output(char *file, char *token)
{
	if (ft_strnstr(token, "GREAT", 5))
		return(fd_outfile(file));
	else if (ft_strnstr(token, "DGREAT", 6))
		return(fd_outfile_append(file));
	return (-10);
}

int	get_outfile_fd(char **token, char **arr)
{
	int	outfile;
	int	i;
	
	outfile = 1;
	i = -1;
	while (token[++i] != NULL)
	{
		if (is_output_redirector(token[i]))
			outfile = redirect_output(arr[i + 1], token[i]);
	}
	return (outfile);
}

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

/*	JOINS '>' + '>' AND '<' + '<' IF NEEDED */
char	**join_d_redirector(char **arr)
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
char	**get_token_list(char **arr)
{
	char	**tokens;
	int		i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	tokens = (char **)malloc(sizeof(char *) * i + 1);
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

char	*add_toarray(char *str, char *str2)
{
	if (!str)
		str = str2;
	else
	{
		str = ft_strjoin(str, " ");
		str = ft_strjoin(str, str2);
	}
	return (str);
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
		if (tokens[i] != NULL)
			arr[new_i] = arr[i];
		else
			arr[new_i] = NULL;
		new_i++;
		i++;
	}
	while (tokens[new_i] != NULL)
	{
		arr[new_i] = NULL;
		new_i++;
	}
	return (arr);
}

/*  DELETES THE PIPES AND CREATES A CMD ARRAY JOINS CMD AND ARGS 
	AND RETURNS CMDS LIKE ARGV SO THAT ONLY CMD WITH ARGS REMAIN */
char	**extract_cmd_array(char **arr, char **tokens, int size)
{
	char	**cmd_array;
	int		tokens_i;
	int		cmd_checker;
	int		cmd_i;

	cmd_array = (char **)malloc(sizeof(char *) * size + 1);
	tokens_i = 0;
	cmd_i = 0;
	cmd_checker = 0;
	arr = delete_io(arr, tokens);
	tokens = get_token_list(arr);
	while (arr[tokens_i] != NULL)
	{
		if (ft_strnstr(tokens[tokens_i], "PIPE", 4))
		{
			while (!ft_strnstr(tokens[cmd_checker], "PIPE", 4) && ft_strnstr(tokens[cmd_checker], "WORD", 4))
			{
				cmd_array[cmd_i] = add_toarray(cmd_array[cmd_i], arr[cmd_checker]);
				cmd_checker++;
			}
			cmd_checker++;
			cmd_i++;
		}
		tokens_i++;
	}
	while (arr[cmd_checker] != NULL && ft_strnstr(tokens[cmd_checker], "WORD", 4))
	{
		cmd_array[cmd_i] = add_toarray(cmd_array[cmd_i], arr[cmd_checker]);
		cmd_checker++;
	}
	cmd_array[cmd_i + 1] = NULL;
	return (cmd_array);
}

/*	CREATES CMD-TABLE AND STARTS PIPEX */
void	execute_pipes(char **arr, char **tokens, int input_fd)
{
	int		pipe_counter;
	int		i;
	char	**cmd_array;
	
	pipe_counter = get_pipe_amount(tokens);
	cmd_array = extract_cmd_array(arr, tokens, pipe_counter + 1);
	for (int i = 0; cmd_array[i] != NULL; i++)
		printf("CMD_ARR[%d]: %s\n", i, cmd_array[i]);
	// execute pipex von paul
}

/*	CHANGES INFILE IF NEEDED AND GOES INTO PIPEX 
	MAYBE ALSO NEEDS TO CHANGE OUTFILE AND EXECUTE LAST CMD */
void	execute_smart_cmd(char **arr)
{
	char	**token_list;
	int		i;
	int		pipe_amount;
	int		input;

	printf("EXECUTE PIPES\n");
	arr = join_d_redirector(arr);
	token_list = get_token_list(arr);
	i = -1;
	while (token_list[++i] != NULL)
	{
		if (is_input_redirector(token_list[i]))
			input = redirect_input(arr[i + 1], token_list[i]);
	}
	printf("TEST\n");
	execute_pipes(arr, token_list, input);
}

/*	"MAIN" RETURNS ERRORS ETC. */
int	handle_execute(char **arr)
{
	pid_t	id;

	id = fork();
	if (id == 0)
		execute_smart_cmd(arr);
	wait(&id);
	return (0);
}
