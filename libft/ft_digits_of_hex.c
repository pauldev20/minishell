/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digits_of_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:14:43 by pgeeser           #+#    #+#             */
/*   Updated: 2022/05/09 13:14:57 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digits_of_hex(unsigned long long n)
{
	int		digits;

	digits = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		digits++;
	}
	return (digits);
}
