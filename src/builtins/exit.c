/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:30:59 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/14 15:00:17 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(int exit_code)
{
	int	i;

	i = 0;
	while (g_minishell.cmd_array[i])
		free(g_minishell.cmd_array[i++]);
	free(g_minishell.cmd_array);
	exit(exit_code);
}
