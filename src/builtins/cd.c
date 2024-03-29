/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:20:10 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/24 16:20:36 by mhedtman         ###   ########.fr       */
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

void	get_old_pwd(void)
{
	char	**arr;
	char	*pre;
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	arr = (char **)ft_calloc(3, sizeof(char *));
	arr[0] = ft_strdup(cwd);
	pre = ft_strdup("OLDPWD=");
	arr[1] = ft_strjoin(pre, arr[0]);
	builtin_export(arr, 1);
	free(pre);
	free_array(arr);
}

void	get_new_pwd(void)
{
	char	**arr;
	char	*pre;
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	arr = (char **)ft_calloc(3, sizeof(char *));
	arr[0] = ft_strdup(cwd);
	pre = ft_strdup("PWD=");
	arr[1] = ft_strjoin(pre, arr[0]);
	builtin_export(arr, 1);
	free(pre);
	free_array(arr);
}

char	*get_home_path(char *str)
{
	t_env	*env;
	char	*new_path_end;
	char	*new_path_start;

	if (!str_is_equal(str, "~") && str[0] == '~')
	{
		env = get_env_var(g_minishell.envp, "HOME");
		if (!env)
			return (NULL);
		new_path_start = env->value;
		new_path_end = ft_substr(str, 1, ft_strlen(str));
		new_path_start = ft_strjoin(new_path_start, new_path_end);
		free(new_path_end);
		return (new_path_start);
	}
	return (str);
}

int	builtin_cd(char *path)
{
	t_env	*env;
	int		chdir_success;

	env = NULL;
	if (path == NULL)
		env = get_env_var(g_minishell.envp, "HOME");
	else
	{
		env = get_env(path);
		path = get_home_path(path);
	}
	get_old_pwd();
	if (env)
		chdir_success = chdir(env->value);
	else
		chdir_success = chdir(path);
	get_new_pwd();
	if (chdir_success == -1)
	{
		ft_putstr_fd("\033[31mminishell: no such file or directory\n", 2);
		g_minishell.exit_code = 4;
		return (4);
	}
	g_minishell.exit_code = 0;
	return (0);
}
