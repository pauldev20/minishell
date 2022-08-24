/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:09:29 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/24 15:20:22 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// need to sett status!!!!!
void	*print_error(int errtype, char *params, int err)
{
	if (errtype == QUOTE)
		ft_putstr_fd("minishell: error while parsing input", 2);
	ft_putendl_fd(params, 2);
	return (NULL);
}
