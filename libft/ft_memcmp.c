/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:02:42 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/17 15:15:54 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
