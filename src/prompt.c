/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:08:55 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/21 01:00:35 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

static char	*replace_pwd(t_env *home, t_env *pwd)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	if (!home)
		return (pwd->value);
	while (home->value[i] && pwd->value[i] && i < (int)ft_strlen(home->value))
	{
		if (home->value[i] != pwd->value[i])
			return (pwd->value);
		i++;
	}
	j = 0;
	out = (char *)malloc(sizeof(char) * ((ft_strlen(pwd->value)
					- ft_strlen(home->value)) + 2));
	if (!out)
		return (NULL);
	out[j++] = '~';
	while (j++ < (int)(ft_strlen(pwd->value) - ft_strlen(home->value)) + 1)
		out[j - 1] = pwd->value[i++];
	out[j - 1] = '\0';
	return (out);
}

static char	*get_user(t_env *usr)
{
	if (!usr)
		return (ft_strdup("guest"));
	return (ft_strjoin(BLUE, usr->value));
}

char	*get_prompt(t_env *usr, t_env *pwd, t_env *home, int rtn_code)
{
	char	*out;
	char	*front;
	char	*back;
	char	*user;
	char	*tmp;

	user = get_user(usr);
	tmp = ft_strjoin(user, "@minishell ");
	free(user);
	front = ft_strjoin(tmp, GREEN);
	free(tmp);
	if (rtn_code)
		back = ft_strjoin(replace_pwd(home, pwd), "\x1b[31m $ ");
	else
		back = ft_strjoin(replace_pwd(home, pwd), " $ ");
	tmp = ft_strjoin(front, back);
	free(front);
	free(back);
	out = ft_strjoin(tmp, RESET);
	free(tmp);
	return (out);
}
