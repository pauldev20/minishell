/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 13:58:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/09/22 15:33:23 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* TOKEN LIST:
	io_redirector: GREAT word, LESS word, DGREAT word, DLESS word
	pipes: pipes PIPE cmd_args
	cmd_and_args: WORD args
	args: WORD
*/
void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
		((unsigned char *)ptr)[i++] = (unsigned char)value;
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset((char *)s, 0, n);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == src)
		return (dest);
	while (i < n)
	{
		*((unsigned char *)dest + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dest);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	ptr = malloc(size * num);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * num);
	return (ptr);
}

char	*ft_strdup(const char *str1)
{
	int		len;
	char	*ptr;

	len = ft_strlen(str1);
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	return (ft_memcpy(ptr, str1, len + 1));
}

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	y;

	i = 0;
	if (!(*little))
		return ((char *)big);
	while (big[i] && i < len)
	{
		y = 0;
		while (little[y] == big[i + y] && i + y < len)
		{
			y++;
			if (!little[y])
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}

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

void	redirect_input(char *file, char *token)
{
	printf("%s\n", token);
	if (ft_strnstr(token, "LESS", 4))
		dup2(fd_infile(file), STDIN_FILENO);
	else if (ft_strnstr(token, "DLESS", 5))
		return ;
	//make here_doc
}

void	redirect_output(char *file, char *token)
{
	if (ft_strnstr(token, "GREAT", 5))
		dup2(fd_outfile(file), STDOUT_FILENO);
	else if (ft_strnstr(token, "DGREAT", 6))
		dup2(fd_outfile_append(file), STDOUT_FILENO);;
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
			tokens[i] = ft_strdup("LESS");
		}
		else if (arr[i][0] == '>')
		{
			if (arr[i][1] == '>')
				tokens[i] = ft_strdup("DGREAT");
			tokens[i] = ft_strdup("GREAT");
		}
		else
			tokens[i] = ft_strdup("WORD");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

// NEED TO FORK BEFORE TO MAKE A OWN PROCESS FOR THE REDIRECTION ALREADY
void	execute_pipes(char **arr)
{
	char	**token_list;
	int		i;
	int		pipe_amount;
	
	printf("EXECUTE PIPES\n");
	token_list = get_token_list(arr);
	i = -1;
	while (token_list[++i] != NULL)
	{
		if (is_input_redirector(token_list[i]))	
			redirect_input(arr[i + 1], token_list[i]);
	}
	// start pipex 
	i = -1;
	while (token_list[++i] != NULL)
	{
		if (is_output_redirector(token_list[i])){
			redirect_output(arr[i + 1], token_list[i]);
			printf("ETST");}
	}
}

int	main_pipes(char **arr)
{
	pid_t	id;

	id = fork();
	if (id == 0)
	{
		printf("CHILD: %d\n", id);
		execute_pipes(arr);
	}
	else
	{
		printf("PARENT: %d\n", id);
		wait(&id);
	}
	return (0);
}

int main()
{
	char *arr[] = {
		"wc",
		"|",
		"test",
		"-l",
		">",
		"outfile",
		"<",
		"infile",
		NULL,
	};
	main_pipes(arr);
	return 0;
}