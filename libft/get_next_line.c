/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:28:50 by pgeeser           #+#    #+#             */
/*   Updated: 2022/09/28 15:37:23 by mhedtman         ###   ########.fr       */
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
		
	while (!ft_strchr(save, '\n') && read_rtn)
	{
		read_rtn = read(fd, buf, BUFFER_SIZE);
		if (read_rtn == -1)
			free(buf);
		if (read_rtn == -1)
			return (NULL);
		buf[read_rtn] = '\0';
		save = ft_strjoin(save, buf);
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
	(*rtn) = ft_substr(save, 0, rtn_len);
	if (!*rtn || !**rtn)
	{
		if (*rtn)
			free(*rtn);
		free(save);
		return (NULL);
	}
	newsave = ft_substr(save, rtn_len, save_len);
	free(save);
	return (newsave);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*rtn;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
		return (NULL);
	rtn = ft_strdup("");
	printf("TEST\n");
	save = read_line(fd, save);
	if (!save)
		return (NULL);
	printf("TEST\n");
	save = create_rtn(save, &rtn);
	if (!save)
		return (NULL);
	printf("RET: %s\n", rtn);
	return (rtn);
}
