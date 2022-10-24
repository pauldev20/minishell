/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:28:57 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/24 03:03:08 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *str, int character)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == (char)character)
			return ((char *)str);
		str++;
	}
	if ((char)character == 0)
		return ((char *)str);
	return (NULL);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len + start > s_len)
		len = s_len - start;
	if (start >= s_len)
		len = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (len + 1))
		((unsigned char *)ptr)[i++] = 0;
	i = 0;
	while (i < len)
		ptr[i++] = *(start + s++);
	return (ptr);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = 0;
	}
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i++])
		ptr[i - 1] = s1[i - 1];
	i -= 1;
	while (*s2)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}
