/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:19:15 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/25 10:25:07 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "minishell.h"


bool	check_squotes(char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (str[i] != '$' && str)
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
	while (str[i] != '$' && str)
	{
		if (str[i] == '\"')
			ret++;
		i++;
	}
	// if (ret % 2 == 0)
	// 	return (false);
	return (true - squotes_first(str, i));
}

int	ft_word_len(char *str)
{
	int i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0'
		&& str[i] != '\"' && str[i] != '\'')
		i++;
	return (i);
}

char	*get_substr_var(char *str, int index)
{
	int		i;
	t_env	*env;
	char	*new_str;
	char	*pre_str;
	char	*to_replace;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			pre_str = ft_substr(str, 0, i);
			to_replace = ft_substr(str + i + 1, 0, ft_word_len(str + 1 + i));
			break ;
		}
		i++;
	}
	env = get_env_var(g_minishell.envp, to_replace);
	if (env != NULL)
		new_str = ft_strdup(env->value);
	else
		new_str = "";
	new_str = ft_strjoin(pre_str, new_str);
	new_str = ft_strjoin(new_str, str + i + 1 + ft_word_len(str + 1 + i));
	return (new_str);
}

char	*expand_vars(char *str)
{
	int	d_quotes;
	int	s_quotes;
	int	i;

	i = 0;
	while (str[i] != '\0' && str != NULL)
	{
		s_quotes = check_squotes(str);
		d_quotes = check_dquotes(str);
		i++;
	}
	printf("%d\n", d_quotes);
	if (d_quotes > 0)
	{
		str = get_substr_var(str, ++i);
		printf("change!\n");
	}
	return (str);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	g_minishell.envp = NULL;
// 	g_minishell.envp = parse_array_to_env(envp, g_minishell.envp);
// 	printf("%s\n", expand_vars("\"\"check $USER test\"\""));
// 	printf("%s\n", expand_vars("$USER"));
// 	printf("%s\n", expand_vars("\'\'\"$USER\""));
// 	printf("%s\n", expand_vars("\'$USER\'"));
// 	printf("%s\n", expand_vars("\"\'$USER\'\""));
// 	printf("%s\n", expand_vars("\'\"$USER\"\'"));
// }