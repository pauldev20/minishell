/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:31:47 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/17 15:21:11 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (0);
	else
		minishell();
	return (1);
}
