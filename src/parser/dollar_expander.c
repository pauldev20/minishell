/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:08:56 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/22 17:09:27 by mhedtman         ###   ########.fr       */
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
	int		i;
	int		counter;
	char	*dollar_str;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			counter++;
		i++;
	}
	dollar_str = ft_strdup("$");
	i = 1;
	while (i < counter)
	{
		dollar_str = ft_strjoin(dollar_str, "$");
		i++;
	}
	return (dollar_str);
}
