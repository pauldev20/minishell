/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:30:59 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/17 21:50:47 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(void)
{
	int	i;

	i = 0;
	while (g_minishell.cmd_array[i])
		free(g_minishell.cmd_array[i++]);
	free(g_minishell.cmd_array);
	exit(0);
}
