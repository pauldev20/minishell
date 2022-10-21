/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:20:10 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/21 12:54:04 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env(char *str)
{
	t_env	*env;

	env = NULL;
	if (str_is_equal(str, "-"))
		env = get_env_var(g_minishell.envp, "OLDPWD");
	else if (str_is_equal(str, "~"))
		env = get_env_var(g_minishell.envp, "HOME");
	else if (str_is_equal(str, "~+"))
		env = get_env_var(g_minishell.envp, "PWD");
	else if (str_is_equal(str, "~-"))
		env = get_env_var(g_minishell.envp, "PWD");
	return (env);
}

int	builtin_cd(char *path)
{
	t_env	*env;
	int		chdir_success;

	env = NULL;
	if (path == NULL)
		env = get_env_var(g_minishell.envp, "HOME");
	else
		env = get_env(path);
	if (env)
		chdir_success = chdir(env->value);
	else
		chdir_success = chdir(path);
	if (chdir_success == -1)
		ft_putstr_fd("\033[31mminishell: no such file or directory\n", 2);
	if (chdir_success == -1)
		return (4);
	return (0);
}
