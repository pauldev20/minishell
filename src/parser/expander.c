/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:19:15 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/05 16:37:51 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				to_replace = ft_substr(str, 0, ft_word_len(str));
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
	if (d_quotes > 0)
	{
		str = get_substr_var(str, ++i);
		return (str);
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