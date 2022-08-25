/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_like_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:00:53 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/24 10:41:50 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: IMPLEMENT TREE AND CORREC EXECUTION

#include "minishell.h"
#include "parser.h"

void	start_heredoc(char *cmd, char *eof)
{
	if (cmd[0] == '|')
		cmd = NULL;
	(void)eof;
}

void	exe_heredocs(t_token_struct **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->e_token_type == DGREAT)
		{
			start_heredoc(tokens[i - 1]->token, tokens[i + 1]->token);
		}
	}
}

bool	has_io_here(t_token_struct **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->e_token_type == DGREAT)
			return (true);
		i++;
	}
	return (false);
}

bool	add_to_tree(t_tree **tree, t_tree *node)
{
	t_tree	*root;

	root = *tree;
	if (root == NULL)
	{
		(*tree) = node;
		return (true);
	}
	if (node->token->nbr_from_left == root->token->nbr_from_left)
		return (false);
	if (node->token->nbr_from_left < root->token->nbr_from_left)
		return (add_to_tree(&(root->left), node));
	else
		return (add_to_tree(&(root->right), node));
}

void	print_tabs(int amount)
{
	int	i;
	
	i = 0;
	while (i < amount)
	{
		printf("\t");
		i++;
	}
}

void	print_tree(t_tree *tree, int level)
{
	if (!tree)
	{
		print_tabs(level);
		printf("------<TREE EMPTY>-----\n");
		return ;
	}
	print_tabs(level);
	printf("token = %s\n", tree->token->token);
	print_tabs(level);
	printf("left\n");
	print_tree(tree->left, level + 1);
	print_tabs(level);
	printf("right\n");
	print_tree(tree->right, level + 1);
	print_tabs(level);
	printf("done\n");
}

t_tree	*new_node(t_token_struct *token)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->root = NULL;
	node->left = NULL;
	node->right = NULL;
	node->token = token;
	return (node);
}

t_tree	*get_tree(t_token_struct **tokens)
{
	t_tree	*tree;
	t_tree	*root;
	int		i;

	root = new_node(tokens[0]);
	i = 1;
	while (tokens[i] != NULL)
	{
		tree = new_node(tokens[i]);
		add_to_tree(&root, tree);
		i++;
	}
	return (root);
}

void	parse_input(char *input)
{
	t_token_struct	**tokens;
	t_tree			*tree;
	
	tokens = parse_tokens(input);
	for (int i = 0; tokens[i] != NULL; i++)
		printf("%s, %d\n", tokens[i]->token, tokens[i]->nbr_from_left);
	// if (has_io_here(tokens))
	// 	exe_heredocs(tokens);
	// else
		// tree = get_tree(tokens);
}