/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:20:10 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/19 16:24:32 by mhedtman         ###   ########.fr       */
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
	if (chdir_success == -1)
	{
		ft_putstr_fd("\033[31mminishell: no such file or directory\n", 2);
		return (4);
	}
	if (pipe_amount > 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
