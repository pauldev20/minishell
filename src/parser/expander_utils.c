/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:37:36 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/10 16:36:13 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_squotes(char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (str[i] != '$' && str && str[i] != '\0')
	{
		if (str[i] == '\'')
			ret++;
		i++;
	}
	if (ret % 2 == 0)
		return (false);
	return (true);
}

bool	squotes_first(char *str, int limit)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (i < limit && str[i] != '\"')
	{
		if (str[i] == '\'')
			ret++;
		i++;
	}
	if (ret % 2 == 0)
		return (false);
	return (true);
}

bool	check_dquotes(char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (str[i] != '$' && str && str[i] != '\0')
	{
		if (str[i] == '\"')
			ret++;
		i++;
	}
	return (true - squotes_first(str, i));
}

int	ft_word_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != ' '
		&& str[i] != '\"' && str[i] != '\''
		&& str[i] != '\n' && str[i] != '$')
		i++;
	return (i);
}
