/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:08:56 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/24 12:39:40 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_delimiter(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			return (true);
		i++;
	}
	return (false);
}

bool	has_only_dollars(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			while (str[i] == '\"' || str[i] == '\'')
				i++;
			if (str[i] && !ft_isalnum(str[i]) && str[i] != '?')
				return (true);
			else if (!str[i])
				return (true);
		}
		i++;
	}
	return (false);
}

char	*get_dollars(char *str)
{
	int		counter;
	char	*dollar_str;
	char	*tmp;

	counter = 0;
	while (*str != '\0')
		if (*str++ == '$')
			counter++;
	dollar_str = ft_strdup("$");
	while (counter-- > 1)
	{
		tmp = dollar_str;
		dollar_str = ft_strjoin(dollar_str, "$");
		free(tmp);
	}
	return (dollar_str);
}
