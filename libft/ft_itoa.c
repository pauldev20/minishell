/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:50:02 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/17 15:15:15 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_itoa(int n)
{
	long	num;
	int		charsno;
	char	*str;

	num = n;
	charsno = ft_digits_of_int(n) + (n < 0);
	str = (char *)ft_calloc(sizeof(char), charsno + 1);
	if (!str)
		return (NULL);
	str[0] = '-';
	if (n < 0)
		num *= -1;
	while (charsno-- > (n < 0))
	{
		str[charsno] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
