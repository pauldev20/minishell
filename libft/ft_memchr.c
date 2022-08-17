/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 23:12:14 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/17 15:15:51 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	while (num--)
		if (*(unsigned char *)ptr++ == (unsigned char)value)
			return ((void *)(ptr - 1));
	return (NULL);
}
