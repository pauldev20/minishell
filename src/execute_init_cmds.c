/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_init_cmds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:25:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/18 16:35:49 by mhedtman         ###   ########.fr       */
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

t_ct	*memory_allocation_arrays(t_ct *exetable, char **token_array)
{
	int	size;

	size = get_pipe_amount(token_array) + 1;
	exetable->cmd_array = (char **)ft_calloc(size, sizeof(char *));
	exetable->in = (char **)ft_calloc(size, sizeof(char *));
	exetable->in_type = (char **)ft_calloc(size, sizeof(char *));
	exetable->here_docs = (char **)ft_calloc(size, sizeof(char *));
	exetable->out = (char **)ft_calloc(size, sizeof(char *));
	exetable->out_type = (char **)ft_calloc(size, sizeof(char *));
	return (exetable);
}

t_ct	*init_cmd_table(t_ct *table, char **cmds, int st_st[2], int i)
{
	char	**tokens;

	tokens = get_token_array(cmds);
	table->cmd_array[i] = get_cmd_array(cmds, tokens, st_st[0], st_st[1]);
	table->in[i] = get_infile(cmds, tokens, st_st[0], st_st[1]);
	table->in_type[i] = get_infile_type(tokens, st_st[0], st_st[1]);
	table->out[i] = get_outfile(cmds, tokens, st_st[0], st_st[1]);
	table->out_type[i] = get_outfile_type(tokens, st_st[0], st_st[1]);
	return (table);
}

t_ct	*get_cmd_table(char **token_array, char **cmd_array)
{
	t_ct		*cmd_table;
	int			st_st[2];
	int			i;

	cmd_table = (t_ct *)malloc(sizeof(t_ct));
	cmd_table = memory_allocation_arrays(cmd_table, token_array);
	st_st[0] = 0;
	st_st[1] = 0;
	i = 0;
	while (token_array[st_st[1]] != NULL)
	{
		if (str_is_equal(token_array[st_st[1]], "PIPE"))
		{
			cmd_table = init_cmd_table(cmd_table, cmd_array, st_st, i);
			i++;
			st_st[0] = st_st[1];
		}
		st_st[1]++;
	}
	cmd_table->here_docs = get_here_doc_limiters(cmd_array);
	cmd_table = init_cmd_table(cmd_table, cmd_array, st_st, i);
	return (cmd_table);
}
