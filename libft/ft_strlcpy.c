/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 00:54:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/17 15:16:34 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	while ((count + 1) < size && src[count] != '\0')
	{
		dest[count] = src[count];
		count++;
	}
	if (size > 0)
		dest[count] = '\0';
	return (ft_strlen(src));
}
