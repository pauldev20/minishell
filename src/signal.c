/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 23:34:45 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/22 02:04:09 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	(void)sig;
	g_minishell.sigint = 1;
	if (g_minishell.pid == -1)
	{
		if (g_minishell.executing)
		{
			// ioctl(STDIN_FILENO, TIOCSTI, "\n");
			// rl_on_new_line();
			// // rl_on_new_line();
			// // rl_replace_line("", 0);
			// // rl_redisplay();
			ioctl(STDIN_FILENO, TIOCSTI, "\r");
			// write(STDIN_FILENO, "aaa\r", 5);
			return ;
		}
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		write(1, "  \n", 3);
}
