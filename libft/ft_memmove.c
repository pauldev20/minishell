/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:37:41 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/07 19:34:24 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t num)
{
	if (dest == src)
		return (dest);
	if (src < dest)
		while (num--)
			*((unsigned char *)dest + num) = *((unsigned char *)src + num);
	else
		ft_memcpy(dest, src, num);
	return (dest);
}
