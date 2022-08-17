/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:50:02 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/13 17:35:06 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
