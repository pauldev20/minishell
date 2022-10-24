/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:05:48 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/24 02:52:33 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int character)
{
	if (str == NULL)
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
