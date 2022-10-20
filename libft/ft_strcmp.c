/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:46:34 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/20 11:47:17 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1)
	{
		if (*str1 != *str2)
			return ((unsigned int)*str2 - (unsigned int)*str1);
		str1++;
		str2++;
	}
	return ((unsigned int)*str2 - (unsigned int)*str1);
}
