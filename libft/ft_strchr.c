/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:05:48 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/17 15:16:24 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *str, int character)
{
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
