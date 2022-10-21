/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 23:34:45 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/21 20:31:12 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	(void)sig;
	g_minishell.sigint = 1;
	if (g_minishell.pid == -1)
	{
		printf("HAAAAAAAA\n");
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_minishell.pid == 0)
	{

		// ioctl(STDIN_FILENO, TIOCSTI, "\n");
		// rl_on_new_line();
		// // rl_on_new_line();
		// // rl_replace_line("", 0);
		// // rl_redisplay();
		write(0, "\0", 1);
	}
	else
		write(1, "  \n", 3);
}
