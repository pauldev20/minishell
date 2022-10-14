/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:19:15 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/14 15:29:03 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_of_expanded(char *str)
{
	if (ft_strnstr(str, "PWD", 3) || ft_strnstr(str, "ZSH", 3))
		return (3);
	else if (ft_strnstr(str, "TERM_PROGRAM", 13))
		return (13);
	else if (ft_strnstr(str, "TERM", 4))
		return (4);
	else if (ft_strnstr(str, "HOMEBREW_TEMP", 14))
		return (14);
	return (1);
}

char	*get_substr_var(char *str, int index)
{
	int		i;
	t_env	*env;
	char	*new_str;
	char	*pre_str;
	char	*to_replace;

	i = 0;
	to_replace = NULL;
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (str[i] == '$')
		{
			pre_str = ft_substr(str, 0, i);
			str = str + i + 1;
			if (str)
			{
				to_replace = ft_substr(str, 0, len_of_expanded(str));
				env = get_env_var(g_minishell.envp, to_replace);
			}
			if (env != NULL)
				new_str = ft_strdup(env->value);
			else
				new_str = "";
			if (pre_str != NULL)
				new_str = ft_strjoin(pre_str, new_str);
			new_str = ft_strjoin(new_str, str + ft_word_len(str));
			free(to_replace);
			return (new_str);
		}
		i++;
	}
	return (str);
}

// char	*expand_vars(char *str)
// {
// 	int	d_quotes;
// 	int	s_quotes;
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0' && str != NULL)
// 	{
// 		s_quotes = check_squotes(str);
// 		d_quotes = check_dquotes(str);
// 		i++;
// 	}
// 	if (d_quotes)
// 	{
// 		str = get_substr_var(str, ++i);
// 		return (str);
// 	}
// 	return (str);
// }

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