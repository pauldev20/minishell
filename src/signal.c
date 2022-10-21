/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 23:34:45 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/21 19:16:28 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	(void)sig;
	g_minishell.sigint = 1;
	if (g_minishell.pid == -1)
	{
		// rl_on_new_line();
		// rl_redisplay();
		// // printf("LINE: -%s-\n", rl_line_buffer);
		// write(1, "  \n", 1);
		// // rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		// rl_redisplay();
		// rl_on_new_line();
		// write(1, "  ", 2);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");				
		rl_replace_line("", 0);
		rl_on_new_line();
	}

	// if (g_minishell.executing)
	// {
	// 	// write(1, "  \n", 3);
	// 	ioctl(STDIN_FILENO, TIOCSTI, "hååå");
	// 	return ;
	// }
	// rl_on_new_line();
	// rl_redisplay();
	// write(1, "  \n", 3);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
	// ioctl(STDIN_FILENO, TIOCSTI, "\n");
}
