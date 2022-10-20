/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 23:34:45 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/21 00:23:01 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_minishell.sigint = 1;
		// ioctl(STDIN_FILENO, TIOCSTI, " ");
		if (g_minishell.executing)
		{
			write(1, "  \n", 3);
			return ;
		}
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
