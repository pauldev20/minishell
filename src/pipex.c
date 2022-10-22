/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:45:24 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/22 14:36:23 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd)
{
	t_env	*env;
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	env = get_env_var(g_minishell.envp, "PATH");
	if (access(cmd, X_OK | F_OK) != -1)
		return (cmd);
	if (!env || cmd[0] == '.' || cmd[0] == '/')
		return (NULL);
	paths = ft_split(env->value + 5, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	free_array(paths);
	return (0);
}

char	**get_cmd_arg_arr(char *cmd, char **args)
{
	char	**full_arr;
	int		i;
	int		c;

	i = 0;
	while (args[i] != NULL)
		i++;
	full_arr = (char **)ft_calloc(i + 2, sizeof(char *));
	full_arr[0] = cmd;
	i = 1;
	c = 0;
	while (args[c] != NULL)
	{
		full_arr[i] = args[c];
		c++;
		i++;
	}
	return (full_arr);
}

/* Function that take the command and send it to find_path
 before executing it. */
int	execute(char *cmd, char **args, char **envp)
{
	char	*path;
	char	**cmd_args;

	if (is_own_builtin(cmd))
		return (execute_own_builtin(cmd, args));
	if (str_is_equal(cmd, "."))
		print_error(3, NULL, 2);
	cmd = delete_quotes(cmd);
	path = find_path(cmd);
	if (str_is_equal(cmd, "") || !cmd)
		return (127);
	if (!path)
		print_error(3, NULL, 127);
	cmd_args = get_cmd_arg_arr(cmd, args);
	if (execve(path, cmd_args, envp) == -1)
		print_error(3, NULL, 127);
	return (127);
}

int	child_process(t_ct *ct, char **envp, int i)
{
	pid_t	pid;
	int		fd[2];
	int		in_out[2];

	if (pipe(fd) == -1)
		print_error(3, NULL, 127);
	pid = fork();
	if (pid == -1)
		print_error(3, NULL, 127);
	if (pid == 0)
	{
		close(fd[0]);
		in_out[0] = get_outfile_fd(ct->out_type[i], ct->out[i], fd[1]);
		dup2(in_out[0], STDOUT_FILENO);
		return (execute(ct->cmd_array[i], ct->arg_array[i], envp));
	}
	else
	{
		close(fd[1]);
		waitpid(0, NULL, WNOHANG);
		in_out[1] = get_infile_fd(ct, ct->in_type[i + 1], ct->in[i + 1], fd[0]);
		dup2(in_out[1], STDIN_FILENO);
		close(fd[0]);
	}
	return (255);
}
