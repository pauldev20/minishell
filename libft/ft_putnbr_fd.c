/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:39:17 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/17 15:16:12 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		digits;
	int		i;
	int		v;
	long	num;
	long	nb;

	i = 0;
	nb = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	digits = ft_digits_of_int(nb);
	while (i < digits)
	{
		num = nb;
		v = digits - 1 - i++;
		while (v--)
			num /= 10;
		ft_putchar_fd((num % 10) + '0', fd);
	}
}
