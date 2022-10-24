/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:28:50 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/24 03:03:13 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *save)
{
	int		read_rtn;
	char	*buf;

	read_rtn = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf && save)
		free(save);
	if (!buf)
		return (NULL);
	while (!gnl_strchr(save, '\n') && read_rtn)
	{
		read_rtn = read(fd, buf, BUFFER_SIZE);
		if (read_rtn == -1)
			free(buf);
		if (read_rtn == -1)
			return (NULL);
		buf[read_rtn] = '\0';
		save = gnl_strjoin(save, buf);
	}
	free(buf);
	return (save);
}

char	*create_rtn(char *save, char **rtn)
{
	int		save_len;
	int		rtn_len;
	char	*newsave;

	rtn_len = 0;
	while (save[rtn_len] && save[rtn_len] != '\n')
		rtn_len++;
	save_len = 0;
	while (save[rtn_len + save_len])
		save_len++;
	if (save[rtn_len] == '\n')
		rtn_len++;
	(*rtn) = gnl_substr(save, 0, rtn_len);
	if (!save[rtn_len] && !**rtn)
	{
		free(*rtn);
		free(save);
		return (NULL);
	}
	newsave = gnl_substr(save, rtn_len, save_len);
	free(save);
	return (newsave);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*rtn;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > FD_SETSIZE)
		return (NULL);
	save = read_line(fd, save);
	if (!save)
		return (NULL);
	save = create_rtn(save, &rtn);
	if (!save)
		return (NULL);
	return (rtn);
}
