/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:37:38 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/06 15:54:53 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int character)
{
	int	len;

	len = ft_strlen(str);
	str += len;
	while (len-- >= 0)
		if (*str-- == (char)character)
			return ((char *)str + 1);
	return (NULL);
}
