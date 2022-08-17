/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:02:42 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/02 22:16:26 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	if (!num)
		return (0);
	while (*((unsigned char *)ptr1) == *((unsigned char *)ptr2) && (num > 1))
	{
		ptr1++;
		ptr2++;
		num--;
	}
	return (*((unsigned char *)ptr1) - *((unsigned char *)ptr2));
}
