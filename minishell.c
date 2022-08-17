/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:07:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/17 15:08:47 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	minishell(char **argv)
{
	char	*input;

	while (1)
	{
		input = readline("minishell: ");
		add_history(input);
	}
	free (input);
	return (0);
}