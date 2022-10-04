/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:45:24 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/04 15:10:32 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
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

/* A simple error displaying function. */
void	error(void)
{
	perror("\033[31mminishell");
	exit(EXIT_FAILURE);
}

/* A simple function to cut the cmd array in the right amount neede*/
char	**cut_start_stop(char **cmd, int start_stop[2])
{
	int	i;

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
	return (cmd);
}

/* Function that take the command and send it to find_path
 before executing it. */
void	execute(char **cmd, char **envp, int start_stop[2])
{
	int		i;
	char	*path;

	i = -1;
	if (access(cmd[start_stop[0]], X_OK | F_OK) == -1)
		path = find_path(cmd[start_stop[0]], envp);
	// else if (is_own_builtin(cmd,start_stop))
	// 	execute_own_builtin(cmd, start_stop);
	else
		path = cmd[start_stop[0]];
	if (cmd[start_stop[0]] == NULL)
		return ;
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	cmd = cut_start_stop(cmd, start_stop);
	if (execve(path, cmd, envp) == -1)
		return ;
}

void	child_process(char **cmd_args, char **envp, int start_stop[2])
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(cmd_args, envp, start_stop);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
