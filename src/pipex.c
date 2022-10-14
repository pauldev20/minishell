/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:45:24 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/14 10:46:41 by mhedtman         ###   ########.fr       */
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

/* Function that take the command and send it to find_path
 before executing it. */
void	execute(char **cmd, char **envp)
{
	int		i;
	char	*path;

	i = -1;
	if (is_own_builtin(cmd))
	{
		execute_own_builtin(cmd);
		return ;
	}
	if (access(cmd[0], X_OK | F_OK) == -1)
		path = find_path(cmd[0]);
	else
		path = cmd[0];
	if (cmd[0] == NULL)
		return ;
	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		return ;
}

void	child_process(t_execute_table *execute_table, char **envp, int i)
{
	pid_t	pid;
	int		fd[2];
	int		in_out[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		printf("TYPE [%s] OUT [%s]\n", execute_table->outfile_type[i], execute_table->outfiles[i]);
		in_out[0] = get_outfile_fd(execute_table->outfile_type[i], execute_table->outfiles[i], fd[1]);
		dup2(in_out[0], STDOUT_FILENO);
		execute(ft_split(execute_table->cmd_array[i], ' '), envp);
	}
	else
	{
		close(fd[1]);
		printf("TYPE [%s] IN [%s]\n", execute_table->infile_type[i], execute_table->infiles[i]);
		in_out[1] = get_infile_fd(execute_table, execute_table->infile_type[i], execute_table->infiles[i], fd[0]);
		dup2(in_out[1], STDIN_FILENO);
		close(fd[0]);
	}
}
