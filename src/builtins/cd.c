/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:20:10 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/14 15:20:36 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char *path, int pipe_amount)
{
	t_env	*env;
	int		chdir_success;

	if (path == NULL)
	{
		env = get_env_var(g_minishell.envp, "HOME");
		path = env->value;
	}
	chdir_success = chdir(path);
	if (pipe_amount > 0)
		return(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
