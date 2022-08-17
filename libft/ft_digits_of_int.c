/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digits_of_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:32:14 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/13 17:34:44 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_digits_of_int(long n)
{
	int		digits;

	digits = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}
