/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:09:29 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/05 14:57:27 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*print_error(int errtype, char *params, int err)
{
	if (errtype == QUOTE)
		ft_putstr_fd("minishell: error while parsing input", 2);
	ft_putendl_fd(params, 2);
	return (NULL);
}
