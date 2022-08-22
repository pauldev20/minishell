/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/22 16:58:03 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

char	*get_quotes_str(char *str, int *len)
{
	char	*ret;

	str ++;
	*len = get_len_quotes(str);
	ret = ft_substr(str - 1, 0, *len + 1);
	*len += 2;
	return (ret);
}

char	**split_cmds(char *input, int *argc)
{
	char	**arr;
	int		arr_start;
	int		len;

	*argc = get_arr_words(input);
	arr = (char **)malloc(sizeof(char *) * (*argc + 1));
	arr[*argc] = NULL;
	arr_start = 0;
	while (arr_start < *argc)
	{
		while (*input == ' ')
			input++;
		if (*input == '\"' || *input == '\'')
			arr[arr_start++] = get_quotes_str(input, &len);
		else
		{
			len = get_len_normal(input);
			arr[arr_start++] = ft_substr(input, 0, len);
		}
		input = input + len;
	}
	return (arr);
}

void	init_tree(t_cmd *leaf, t_tree **tree)
{
	(void)tree;
	(void)leaf;
}

void	join_nodes(t_cmd **lst)
{
	char	*cmd_node;

	cmd_node = (*lst)->cmd;
	printf("FIRST CMD in nodes: %s\n", (*lst)->cmd);
	while ((*lst) != NULL)
	{
		if ((*lst)->next != NULL)
		{
			if (!is_delimiter((*lst)->e_token))
				cmd_node = ft_strjoin(cmd_node, (*lst)->cmd);
			printf("%s\n", cmd_node);
		}
		(*lst) = (*lst)->next;
	}	
}

void	parse_input(char *input)
{
	t_cmd	*array;
	t_tree	*tree;
	int		argc;
	int		c;

	g_minishell.cmd_array = split_cmds(input, &argc);
	print_env(g_minishell.envp);
	printf("ARGC: %d\n", argc);
	for (int i = 0; g_minishell.cmd_array[i] != NULL; i++)
		printf("ARGV: %s\n", g_minishell.cmd_array[i]);
	c = 0;
	while (g_minishell.cmd_array[c] != NULL)
	{
		array = init_token(g_minishell.cmd_array[c], array);
		c++;
	}
	for (int i = 0; arra[i] != NULL; i++)
		printf("ARRAY: %s, TOKEN: %u\n");
	printf("FIRST CMD: %s\n", array->cmd);
	join_nodes(&array);
	(void)tree;
	// init_tree(array, &tree);
	//builtin_parser(g_minishell.cmd_array, argc);
}
