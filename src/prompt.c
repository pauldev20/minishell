/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:08:55 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/24 16:16:55 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

static char	*replace_pwd(t_env *home, t_env *pwd)
{
	int		i;
	int		j;
	char	*out;

	if (!home)
		return (pwd->value);
	if (ft_strncmp(home->value, pwd->value, ft_strlen(home->value)) != 0)
		return (ft_strdup(pwd->value));
	j = 0;
	out = (char *)malloc(sizeof(char) * ((ft_strlen(pwd->value)
					- ft_strlen(home->value)) + 2));
	if (!out)
		return (NULL);
	out[j++] = '~';
	i = ft_strlen(home->value);
	while (j++ < (int)(ft_strlen(pwd->value) - ft_strlen(home->value)) + 1)
		out[j - 1] = pwd->value[i++];
	out[j - 1] = '\0';
	return (out);
}

static char	*get_user(t_env *usr)
{
	if (!usr)
		return (ft_strdup("\x1b[31guest"));
	return (ft_strjoin(BLUE, usr->value));
}

static char	*get_front(t_env *usr, t_env *pwd, t_env *home)
{
	char	*user;
	char	*tmp;
	char	*front;

	user = get_user(usr);
	tmp = user;
	user = ft_strjoin(user, "@minishell ");
	free(tmp);
	tmp = user;
	user = ft_strjoin(user, GREEN);
	free(tmp);
	tmp = replace_pwd(home, pwd);
	front = ft_strjoin(user, tmp);
	free(tmp);
	free(user);
	return (front);
}

char	*get_prompt(t_env *usr, t_env *pwd, t_env *home, int rtn_code)
{
	char	*out;
	char	*front;
	char	*tmp;

	front = get_front(usr, pwd, home);
	if (rtn_code)
		tmp = ft_strjoin(front, "\x1b[31m $ ");
	else
		tmp = ft_strjoin(front, "\x1b[92m $ ");
	free(front);
	out = ft_strjoin(tmp, RESET);
	free(tmp);
	return (out);
}
