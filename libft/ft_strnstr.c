/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:10:06 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/13 16:55:24 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	y;

	i = 0;
	if (!(*little))
		return ((char *)big);
	while (big[i] && i < len)
	{
		y = 0;
		while (little[y] == big[i + y] && i + y < len)
		{
			y++;
			if (!little[y])
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
