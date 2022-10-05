/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_tty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:15:21 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/05 10:51:14 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_line(char *str)
{
	free(str);
	return (NULL);
}

char	*append_char(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(str);
	return (new_str);
}

char	*get_terminal_line(int fd)
{
	char		buf;
	char		*rtn;
	int			checker;

	rtn = ft_strdup("");
	checker = read(fd, &buf, 1);
	if (checker == -1 || checker == 0)
		return (free_line(rtn));
	while (checker > 0)
	{
		rtn = append_char(rtn, buf);
		if (rtn == NULL)
			return (NULL);
		if (buf == '\n')
			return (ft_strtrim(rtn, "\n"));
		checker = read(fd, &buf, 1);
	}
	if (checker == -1)
		return (free_line(rtn));
	return (rtn);
}

char	*catch_tty(char *prompt)
{
	char	*str;

	if (isatty(STDIN_FILENO))
		str = readline(prompt);
	else
		str = get_terminal_line(STDIN_FILENO);
	if (str == NULL)
		return (NULL);
	if (isatty(STDIN_FILENO))
		add_history(str);
	return (str);
}
