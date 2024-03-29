/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:22:48 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/24 15:50:22 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envd_str(char *str, int key_len)
{
	char	*key;
	t_env	*envvar;

	key = ft_substr(str, 0, key_len);
	str = ft_substr(str, key_len, ft_strlen(str));
	envvar = get_env_var(g_minishell.envp, key);
	free(key);
	if (envvar && (str[0] == '$' || str[0] == '\"' || str[0] == '\''))
	{
		free(str);
		return (ft_strdup(envvar->value));
	}
	else if (envvar)
	{
		key = ft_strjoin(envvar->value, str);
		free(str);
		return (key);
	}
	return (NULL);
}

char	*get_new_str(char *str)
{
	size_t	key_len;
	char	*ret;
	t_env	*envvar;

	key_len = 0;
	envvar = NULL;
	while (str[key_len] != '\0' && str[key_len] != '/' && str[key_len] != '$'
		&& str[key_len] != '\"' && str[key_len] != '\'')
		key_len++;
	if (ft_strlen(str) > key_len)
	{
		ret = get_envd_str(str, key_len);
		return (ret);
	}
	else
		envvar = get_env_var(g_minishell.envp, str);
	if (envvar)
		return (ft_strdup(envvar->value));
	return (NULL);
}

static char	*handle_expand(int (*i)[3], char *(*chars)[3], char *str)
{
	if (!(*i)[2] && str[(*i)[0]] == '$')
	{
		if (has_only_dollars(str))
			return (get_dollars(str));
		if (str[(*i)[0]++ + 1] == '?')
			return (ft_itoa(g_minishell.exit_code));
		(*chars)[1] = get_new_str(str + (*i)[0]);
		if ((*chars)[1])
		{
			(*chars)[2] = (*chars)[0];
			(*chars)[0] = ft_strjoin((*chars)[0], (*chars)[1]);
			free((*chars)[2]);
			free((*chars)[1]);
		}
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
	if (has_delimiter(str))
		return (str);
	chars[0] = ft_calloc(1, sizeof(char));
	while (str[i[0]])
	{
		rtn = check_expand(&i, &chars, str);
		if (rtn && str)
			free(str);
		if (rtn)
			free(chars[0]);
		if (rtn)
			return (rtn);
		i[0]++;
	}
	if (str)
		free (str);
	return (chars[0]);
}
