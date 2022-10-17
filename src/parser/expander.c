/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:19:15 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/17 13:47:04 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*catch_questionmark(char	*str)
{
	write(1, ft_itoa(g_minishell.exit_code), ft_strlen(ft_itoa(g_minishell.exit_code)));
	return (NULL);
}

char	*expand_vars(char *str)
{
	int		i;
	int		doubleq;
	int		singleq;
	char	*to_replace;
	char	*out;
	char	*new;
	char	*old;
	t_env	*envvar;

	i = 0;
	doubleq = 0;
	singleq = 0;
	out = ft_calloc(1, sizeof(char));
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
				if (str[i] == '?')
					return (catch_questionmark(str));
				new = ft_substr(str + i, 0, ft_word_len(str + i));
				envvar = get_env_var(g_minishell.envp, new);
				old = out;
				if (envvar)
				{
					out = ft_strjoin(out, envvar->value);
					free(old);
				}
				i += ft_word_len(str + i) - 1;
				free(new);
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
	return (out);
}
	 