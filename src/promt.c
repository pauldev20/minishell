/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:08:55 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/22 14:45:03 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_pwd(char *home, char *pwd)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	while (home[i] && pwd[i] && i < (int)ft_strlen(home))
	{
		if (home[i] != pwd[i])
			return (NULL);
		i++;
	}
	j = 0;
	out = (char *)malloc(sizeof(char) * (ft_strlen(pwd) - ft_strlen(home) + 2));
	if (!out)
		return (NULL);
	out[j++] = '~';
	while (j++ < (int)(ft_strlen(pwd) - ft_strlen(home) + 2))
		out[j - 1] = pwd[i++];
	out[j - 1] = '\0';
	return (out);
}

static char	*promtstr(t_env *usr, t_env *pwd, t_env *home)
{
	char	*out;
	char	*front;
	char	*back;
	char	*path;

	path = NULL;
	if (!usr)
		front = ft_strjoin("guest", "@minishell ");
	else
		front = ft_strjoin(usr->value, "@minishell ");
	if (home)
		path = replace_pwd(home->value, pwd->value);
	if (home && path)
		back = ft_strjoin(path, " $ ");
	else
		back = ft_strjoin(pwd->value, " $ ");
	out = ft_strjoin(front, back);
	free(front);
	free(back);
	if (path)
		free(path);
	return (out);
}

char	*get_promt(void)
{
	return (promtstr(
			get_env_var(g_minishell.envp, "USER"),
			get_env_var(g_minishell.envp, "PWD"),
			get_env_var(g_minishell.envp, "HOME")
		));
}
