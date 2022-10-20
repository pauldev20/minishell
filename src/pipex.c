/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:45:24 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/20 14:48:32 by mhedtman         ###   ########.fr       */
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

	i = 0;
	if (cmd[0] == '.' || cmd[0] == '/')
		return (NULL);
	env = get_env_var(g_minishell.envp, "PATH");
	paths = ft_split(env->value + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

/* A simple function to cut the cmd array in the right amount neede*/
char	**cut_start_stop(char **cmd, int start_stop[2])
{
	int	i;
	int	start_reset;

	start_reset = start_stop[0];
	i = 0;
	while (start_stop[0] < start_stop[1])
	{
		cmd[i] = cmd[start_stop[0]];
		i++;
		start_stop[0]++;
	}
	while (cmd[i] != NULL)
	{
		cmd[i] = NULL;
		i++;
	}
	start_stop[0] = start_reset;
	return (cmd);
}

char	**get_cmd_arg_arr(char *cmd, char *args)
{
	char	**part_arr;
	char	**full_arr;
	int		i;
	int		c;

	i = 0;
	part_arr = ft_split(args, ' ');
	while (part_arr[i] != NULL)
		i++;
	full_arr = (char **)ft_calloc(i + 2, sizeof(char *));
	full_arr[0] = cmd;
	i = 1;
	c = 0;
	while (part_arr[c] != NULL)
	{
		full_arr[i] = part_arr[c];
		c++;
		i++;
	}
	free(part_arr);
	return (full_arr);
}

/* Function that take the command and send it to find_path
 before executing it. */
int	execute(char *cmd, char *args, char **envp)
{
	char	*path;
	char	**cmd_args;

	if (is_own_builtin(cmd))
		return (execute_own_builtin(cmd, args));
	if (str_is_equal(cmd, "."))
		print_error(3, NULL, 2);
	if (access(cmd, X_OK | F_OK) == -1)
		path = find_path(cmd);
	else
		path = cmd;
	if (str_is_equal(cmd, "") || !cmd)
		return (127);
	if (!path)
	{
		free(args);
		free(cmd);
		print_error(3, NULL, 127);
	}
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
