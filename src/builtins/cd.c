/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:20:10 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/06 09:39:55 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char *path, int pipe_amount)
{
	char	cwd[PATH_MAX];
	t_env	*env;

	if (path == NULL)
	{
		env = get_env_var(g_minishell.envp, "HOME");
		path = env->value;
	}
	chdir(path);
	if (pipe_amount > 0)
		exit (0);
	return (EXIT_SUCCESS);
}
