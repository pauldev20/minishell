/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_tty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:15:21 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/21 19:58:28 by pgeeser          ###   ########.fr       */
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
	free(prompt);
	if (str == NULL)
		return (NULL);
	if (*str != '\0' && isatty(STDIN_FILENO))
		add_history(str);
	return (str);
}
