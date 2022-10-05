/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:14:57 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/05 16:29:18 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

int	get_here_doc_amount(char **arr)
{
	char	**tokens;
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	tokens = get_token_array(arr);
	while (tokens[i] != NULL)
	{
		if (ft_strnstr(tokens[i], "DLESS", 5))
			ret++;
		i++;
	}
	return (ret);
}

char	**get_here_doc_limiters(char **arr)
{
	int		i;
	int		limiter_i;
	int		here_doc_amount;
	char	**limiter;
	char	**tokens;

	limiter_i = 0;
	i = 0;
	tokens = get_token_array(arr);
	here_doc_amount = get_here_doc_amount(arr);
	limiter = (char **)malloc(sizeof(char *) * (here_doc_amount + 1));
	while (tokens[i] != NULL)
	{
		if (ft_strnstr(tokens[i], "DLESS", 5))
		{
			limiter[limiter_i] = arr[i + 1];
			limiter_i++;
		}
		i++;
	}
	limiter[limiter_i] = NULL;
	return (limiter);
}

char	**duplicate_arr(char **arr)
{
	char	**new_arr;
	int		i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	new_arr = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (arr[i] != NULL)
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

void	execute_here_doc(char **arr)
{
	int		start_stop[2];
	char	**new_arr;
	char	**cmd;
	int		fd;

	new_arr = duplicate_arr(arr);
	cmd = (char **)malloc(sizeof(char *) * 2);
	cmd[0] = ft_strdup("cat");
	cmd[1] = NULL;
	start_stop[0] = 0;
	start_stop[1] = 1;
	new_arr = delete_io(new_arr, get_token_array(new_arr));
	if (new_arr[0] == NULL)
	{
		fd = open("/tmp/here_doc", O_RDONLY, 0777);
		dup2(fd, STDIN_FILENO);
		execute(cmd, environ, start_stop);
	}
	else
		free_array(new_arr);
}

void	here_doc_execute(char *limiter, char **arr)
{
	char	*line;
	int		fd;
	char	**here_doc_limiters;
	int		i;

	i = 0;
	fd = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 00777);
	here_doc_limiters = get_here_doc_limiters(arr);
	while (1)
	{
		write(1, "\e[1;34mheredoc> \e[0m", 21);
		line = expand_vars(get_next_line(STDIN_FILENO));
		if (ft_strnstr(line, here_doc_limiters[i],
				ft_strlen(here_doc_limiters[i])))
		{
			i++;
			if (here_doc_limiters[i] == NULL)
			{
				free(line);
				close(fd);
				execute_here_doc(arr);
				return ;
			}
		}
		else
		{
			write(fd, line, ft_strlen(line));
			free(line);
		}
	}
}
