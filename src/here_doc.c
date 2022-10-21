/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:14:57 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/21 18:20:04 by pgeeser          ###   ########.fr       */
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

bool	has_dollars(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

char	*get_here_doc_line(void)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	if (has_dollars(line))
		line = expand_vars(line);
	return (line);
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
		line = get_here_doc_line();
		if (*line == '\n' && g_minishell.sigint)
		{
			free(line);
			break ;
		}
		if (str_is_equal(exe_table->here_docs[i], line))
		{
			if (exe_table->here_docs[i++] == NULL)
				free(line);
			if (exe_table->here_docs[i++] == NULL)
				return ;
			fd = open("/tmp/here_doc", O_WRONLY | O_TRUNC, 00777);
		}
		else
			write(fd, line, ft_strlen(line));
		free(line);
	}
}
