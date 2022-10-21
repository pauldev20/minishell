/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:22:48 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/21 19:24:47 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_str(char *str)
{
	size_t	key_len;
	char	*key;
	t_env	*envvar;

	key_len = 0;
	while (str[key_len] != '\0' && str[key_len] != '/' && str[key_len] != '$'
		&& str[key_len] != '\"' && str[key_len] != '\'')
		key_len++;
	if (ft_strlen(str) > key_len)
	{
		key = ft_substr(str, 0, key_len);
		str = ft_substr(str, key_len, ft_strlen(str));
		envvar = get_env_var(g_minishell.envp, key);
		if (envvar && (str[0] == '$' || str[0] == '\"' || str[0] == '\''))
			return (ft_strdup(envvar->value));
		else if (envvar)
			return (ft_strjoin(envvar->value, str));
	}
	else
	{
		envvar = get_env_var(g_minishell.envp, str);
		if (envvar)
			return (ft_strdup(ft_strdup(envvar->value)));
	}
	return (NULL);
}

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

static char	*handle_expand(int (*i)[3], char *(*chars)[3], char *str)
{
	if (!(*i)[2] && str[(*i)[0]] == '$')
	{
		(*i)[0]++;
		if (str[(*i)[0]] == 0)
			return (ft_strdup("$"));
		if (str[(*i)[0]] == '?')
			return (ft_itoa(g_minishell.exit_code));
		(*chars)[1] = get_new_str(str + (*i)[0]);
		if ((*chars)[1])
			(*chars)[0] = ft_strjoin((*chars)[0], (*chars)[1]);
		free((*chars)[1]);
		(*i)[0] += ft_word_len(str + (*i)[0]) - 1;
	}
	else
	{
		(*chars)[1] = ft_substr(str, (*i)[0], 1);
		(*chars)[2] = (*chars)[0];
		(*chars)[0] = ft_strjoin((*chars)[0], (*chars)[1]);
		free((*chars)[2]);
		free((*chars)[1]);
	}
	return (NULL);
}

static char	*check_expand(int (*i)[3], char *(*chars)[3], char *str)
{
	char	*rtn;

	(*i)[1] += (str[(*i)[0]] == '\"') * (!(*i)[1] + -((*i)[1]));
	(*i)[2] += (str[(*i)[0]] == '\'' && !(*i)[1]) * (!(*i)[2] + -((*i)[2]));
	if (i[1] && str[(*i)[0]] == '\'')
	{
		(*chars)[2] = (*chars)[0];
		(*chars)[0] = ft_strjoin((*chars)[0], "'");
		free((*chars)[2]);
	}
	else if ((str[(*i)[0]] != '\'' && str[(*i)[0]] != '\"')
		|| (str[(*i)[0]] != '\'' && (*i)[2]))
	{
		rtn = handle_expand(i, chars, str);
		if (rtn)
			return (rtn);
	}
	return (NULL);
}

char	*expand_vars(char *str)
{
	int		i[3];
	char	*chars[3];
	char	*rtn;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	chars[0] = ft_calloc(1, sizeof(char));
	if (has_delimiter(str))
		return (str);
	while (str[i[0]])
	{
		rtn = check_expand(&i, &chars, str);
		if (rtn)
			return (rtn);
		i[0]++;
	}
	free(str);
	return (chars[0]);
}
