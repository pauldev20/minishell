/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:14:57 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/24 17:14:47 by pgeeser          ###   ########.fr       */
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
	free_array(tokens);
	return (ret);
}

char	**get_here_doc_limiters(char **arr)
{
	int		i[2];
	char	*tmp;
	int		here_doc_amount;
	char	**limiter;
	char	**tokens;

	i[1] = 0;
	i[0] = 0;
	tokens = get_token_array(arr);
	here_doc_amount = get_here_doc_amount(arr);
	limiter = (char **)ft_calloc((here_doc_amount + 1), sizeof(char *));
	while (tokens[i[0]] != NULL)
	{
		if (ft_strnstr(tokens[i[0]], "DLESS", 5))
		{
			tmp = ft_strdup(arr[i[0] + 1]);
			limiter[i[1]] = ft_strjoin(tmp, "\n");
			free(tmp);
			i[1]++;
		}
		i[0]++;
	}
	free_array(tokens);
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
	char	*tmp;

	tmp = readline("\e[1;34mheredoc> \e[0m");
	if (!tmp)
	{
		printf("READLINE QUIT: [%s]\n", rl_line_buffer);
		return (NULL);
	}
	line = ft_strjoin(tmp, "\n");
	free(tmp);
	if (has_dollars(line))
		line = expand_vars(line);
	return (line);
}

void	here_doc_execute(char **limiter)
{
	char	*line;
	int		i[2];

	i[0] = 0;
	i[1] = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 00777);
	while (1)
	{
		line = get_here_doc_line();
		if (g_minishell.sigint && line)
			return (free(line));
		if (str_is_equal(limiter[i[0]], line) || line == NULL)
		{
			i[0]++;
			if (limiter[i[0]] == NULL && line)
				free(line);
			if (limiter[i[0]] == NULL || line == NULL)
				return ;
			i[1] = open("/tmp/here_doc", O_WRONLY | O_TRUNC, 00777);
		}
		else
			write(i[1], line, ft_strlen(line));
		free(line);
	}
}
