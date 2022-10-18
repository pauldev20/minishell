/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_init_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:25:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/18 16:12:43 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_array(char **cmds, char **tokens, int start, int stop)
{
	char	*cmd_args;

	cmd_args = ft_strdup("");
	while (start < stop)
	{
		if (str_is_equal(tokens[start], "WORD"))
		{
			if (cmd_args[0] == '\0')
				cmd_args = ft_strjoin(cmd_args, cmds[start]);
			else
			{
				cmd_args = ft_strjoin(cmd_args, " ");
				cmd_args = ft_strjoin(cmd_args, cmds[start]);
			}
		}
		start++;
	}
	return (cmd_args);
}

t_exetable	*memory_allocation_arrays(t_exetable *exetable, char **token_array)
{
	int	size;

	size = get_pipe_amount(token_array) + 1;
	exetable->cmd_array = (char **)ft_calloc(size, sizeof(char *));
	exetable->infiles = (char **)ft_calloc(size, sizeof(char *));
	exetable->infile_type = (char **)ft_calloc(size, sizeof(char *));
	exetable->here_docs = (char **)ft_calloc(size, sizeof(char *));
	exetable->outfiles = (char **)ft_calloc(size, sizeof(char *));
	exetable->outfile_type = (char **)ft_calloc(size, sizeof(char *));
	return (exetable);
}

t_exetable	*init_exetable(t_exetable *table, char **cmds, int st_st[2], int i)
{
	char	**tokens;

	tokens = get_token_array(cmds);
	table->cmd_array[i] = get_cmd_array(cmds, tokens, st_st[0], st_st[1]);
	table->infiles[i] = get_infile(cmds, tokens, st_st[0], st_st[1]);
	table->infile_type[i] = get_infile_type(tokens, st_st[0], st_st[1]);
	table->outfiles[i] = get_outfile(cmds, tokens, st_st[0], st_st[1]);
	table->outfile_type[i] = get_outfile_type(tokens, st_st[0], st_st[1]);
	return (table);
}

t_exetable	*get_exetable(char **token_array, char **cmd_array)
{
	t_exetable	*exetable;
	int			st_st[2];
	int			i;

	exetable = (t_exetable *)malloc(sizeof(t_exetable));
	exetable = memory_allocation_arrays(exetable, token_array);
	st_st[0] = 0;
	st_st[1] = 0;
	i = 0;
	while (token_array[st_st[1]] != NULL)
	{
		if (str_is_equal(token_array[st_st[1]], "PIPE"))
		{
			exetable = init_exetable(exetable, cmd_array, st_st, i);
			i++;
			st_st[0] = st_st[1];
		}
		st_st[1]++;
	}
	exetable->here_docs = get_here_doc_limiters(cmd_array);
	exetable = init_exetable(exetable, cmd_array, st_st, i);
	return (exetable);
}
