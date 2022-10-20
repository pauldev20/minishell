/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:14:57 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/20 11:48:16 by mhedtman         ###   ########.fr       */
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
			limiter[limiter_i] = ft_strjoin(limiter[limiter_i], "\n");
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

void	here_doc_execute(t_ct *exe_table)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 00777);
	while (1)
	{
		write(1, "\e[1;34mheredoc> \e[0m", 21);
		line = expand_vars(get_next_line(STDIN_FILENO));
		if (*line == '\n' && g_minishell.sigint)
			break ;
		if (str_is_equal(exe_table->here_docs[i], line))
		{
			i++;
			if (exe_table->here_docs[i] == NULL)
				return ;
			fd = open("/tmp/here_doc", O_WRONLY | O_TRUNC, 00777);
		}
		else
		{
			write(fd, line, ft_strlen(line));
			free(line);
		}
	}
}
