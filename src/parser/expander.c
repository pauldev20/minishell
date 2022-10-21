/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:22:48 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/21 15:48:10 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_key_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0' && str[len] != '/'
		&& str[len] != '$' && str[len] != '\"'
		&& str[len] != '\'')
		len++;
	return (len);
}

char	*get_new_str(char *str)
{
	size_t	key_len;
	char	*key;
	t_env	*envvar;

	printf("get new str [%s]\n", str);
	key_len = get_key_len(str);
	if (ft_strlen(str) > key_len)
	{
		key = ft_substr(str, 0, key_len);
		str = ft_substr(str, key_len, ft_strlen(str));
		envvar = get_env_var(g_minishell.envp, key);
		if (envvar && (str[0] == '$' || str[0] == '\"'))
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

char	*expand_vars(char *str)
{
	int		i;
	int		doubleq;
	int		singleq;
	char	*out;
	char	*new;
	char	*old;

	i = 0;
	printf("str [%s]\n", str);
	doubleq = 0;
	singleq = 0;
	out = ft_calloc(1, sizeof(char));
	if (has_delimiter(str))
		return (str);
	while (str[i])
	{
		if (str[i] == '\"')
			doubleq = !doubleq;
		if (str[i] == '\'' && !doubleq)
			singleq = !singleq;
		if (doubleq && str[i] == '\'')
		{
			old = out;
			out = ft_strjoin(out, "'");
			free(old);
		}
		else if ((str[i] != '\'' && str[i] != '\"')
			|| (str[i] != '\'' && singleq))
		{
			if (!singleq && str[i] == '$')
			{
				i++;
				if (str[i] == 0)
					return (ft_strdup("$"));
				if (str[i] == '?')
					return (ft_itoa(g_minishell.exit_code));
				new = get_new_str(str + i);
				if (new)
					out = ft_strjoin(out, new);
				free(new);
				i += ft_word_len(str + i) - 1;
			}
			else
			{
				new = ft_substr(str, i, 1);
				old = out;
				out = ft_strjoin(out, new);
				free(old);
				free(new);
			}
		}
		i++;
	}
	free(str);
	printf("OUT [%s]\n", out);
	return (out);
}
