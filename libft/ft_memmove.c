/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:37:41 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/17 15:16:00 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
