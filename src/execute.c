/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/09/26 16:11:44 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* TOKEN LIST:
	io_redirector: GREAT word, LESS word, DGREAT word, DLESS word
	pipes: pipes PIPE cmd_args
	cmd_and_args: WORD args
	args: WORD
*/
// void	*ft_memset(void *ptr, int value, size_t num)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < num)
// 		((unsigned char *)ptr)[i++] = (unsigned char)value;
// 	return (ptr);
// }

// void	ft_bzero(void *s, size_t n)
// {
// 	ft_memset((char *)s, 0, n);
// }

// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (dest == src)
// 		return (dest);
// 	while (i < n)
// 	{
// 		*((unsigned char *)dest + i) = *((unsigned char *)src + i);
// 		i++;
// 	}
// 	return (dest);
// }

// size_t	ft_strlen(const char *str)
// {
// 	size_t	len;

// 	len = 0;
// 	while (str[len])
// 		len++;
// 	return (len);
// }

// void	*ft_calloc(size_t num, size_t size)
// {
// 	void	*ptr;

// 	ptr = malloc(size * num);
// 	if (!ptr)
// 		return (NULL);
// 	ft_bzero(ptr, size * num);
// 	return (ptr);
// }

// char	*ft_strdup(const char *str1)
// {
// 	int		len;
// 	char	*ptr;

// 	len = ft_strlen(str1);
// 	ptr = (char *)ft_calloc(len + 1, sizeof(char));
// 	if (!ptr)
// 		return (NULL);
// 	return (ft_memcpy(ptr, str1, len + 1));
// }

// char	*ft_strnstr(const char	*big, const char *little, size_t len)
// {
// 	size_t	i;
// 	size_t	y;

// 	i = 0;
// 	if (!(*little))
// 		return ((char *)big);
// 	while (big[i] && i < len)
// 	{
// 		y = 0;
// 		while (little[y] == big[i + y] && i + y < len)
// 		{
// 			y++;
// 			if (!little[y])
// 				return ((char *)big + i);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

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

int		get_outfile_fd(char **token, char **arr)
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

// void	child_process(char *cmd)
// {
// 	pid_t	pid;
// 	int		fd[2];

// 	if (pipe(fd) == -1)
// 		error();
// 	pid = fork();
// 	if (pid == -1)
// 		error();
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		execute(cmd);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		waitpid(pid, NULL, 0);
// 	}
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (*s1)
		ptr[i++] = *s1++;
	while (*s2)
		ptr[i++] = *s2++;
	return (ptr);
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

bool	is_io(char *token)
{
	if (is_input_redirector(token) == true || is_output_redirector(token) == true)
			return (true);
	return (false);
}

char	**delete_io(char **arr, char **tokens)
{
	int		i;
	int		new_i;

	new_i = 0;
	i = 0;
	while (tokens[i] != NULL)
	{
		if (is_io(tokens[i]))
			i =  i + 2;
		else
		{
			arr[new_i] = arr[i];
			new_i++;
			i++;
		}
	}
	while (tokens[new_i] != NULL)
	{
		arr[new_i] = NULL;
		new_i++;
	}
	return (arr);
}

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
	// i  = -1;
	// dup2(input_fd, STDIN_FILENO);
	// execute(cmd_array[0]);
	// i = 0;
	// while (++i < pipe_counter)
	// 	child_process(cmd_array[i]);
	// dup2(get_outfile_fd(tokens, arr), STDOUT_FILENO);
	// execute_last(cmd_array[pipe_counter + 1]);
}

// NEED TO FORK BEFORE TO MAKE A OWN PROCESS FOR THE REDIRECTION ALREADY
void	execute_smart_cmd(char **arr)
{
	char	**token_list;
	int		i;
	int		pipe_amount;
	int		input;

	printf("EXECUTE PIPES\n");
	token_list = get_token_list(arr);
	i = -1;
	while (token_list[++i] != NULL)
	{
		if (is_input_redirector(token_list[i]))
			input = redirect_input(arr[i + 1], token_list[i]);
	}
	execute_pipes(arr, token_list, input);
}

int	handle_execute(char **arr)
{
	pid_t	id;

	id = fork();
	if (id == 0)
		execute_smart_cmd(arr);
	wait(&id);
	return (0);
}

// int main()
// {
// 	char *arr[] = {
// 		"wc",
// 		"-l",
// 		"|",
// 		"echo -wc",
// 		">>",
// 		"outfile",
// 		"|",
// 		"ls",
// 		"-a",
// 		NULL,
// 	};
// 	main_pipes(arr);
// 	return 0;
// }