/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/20 18:00:52 by mhedtman         ###   ########.fr       */
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
	while (leaf)
	{
		printf("%s\n", leaf->cmd);
		leaf = leaf->next;
	}
	while (!is_delimiter(leaf->e_token))
		leaf = leaf->next;
}

void	parse_input(char *input)
{
	t_cmd	*array;
	t_tree	*tree;
	int		argc;

	g_minishell.cmd_array = split_cmds(input, &argc);
	printf("ARGC: %d\n", argc);
	for(int i = 0; g_minishell.cmd_array[i] != NULL; i++)
		printf("ARGV: %s\n", g_minishell.cmd_array[i]);
	while (*g_minishell.cmd_array)
	{
		array = init_token(*g_minishell.cmd_array, array);
		if (*g_minishell.cmd_array)
			g_minishell.cmd_array++;
	}
	init_tree(array, &tree);
	//builtin_parser(g_minishell.cmd_array, argc);
}
