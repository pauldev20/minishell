/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:09:29 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/17 14:50:39 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*print_error(int errtype, char *params, int err)
{
	if (errtype == QUOTE)
		ft_putstr_fd("\033[31mminishell: error while parsing input", 2);
	else if (errtype == BAD_FILE)
		ft_putstr_fd("\033[31mminishell: error while opening file", 2);
	else if (errtype == EXECUTE_ERROR)
		ft_putstr_fd("\033[31mminishell: error while executing file", 2);
	else if (errtype == CD)
		ft_putstr_fd("\033[31mminishell: no such file or directory", 2);
	ft_putendl_fd(params, 2);
	exit (err);
}
