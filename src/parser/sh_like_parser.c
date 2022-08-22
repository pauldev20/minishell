/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_like_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:00:53 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/22 13:32:39 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// TODO: IMPLEMENT TREE AND CORREC EXECUTION

#include "minishell.h"
#include "parser.h"

bool	check_dollar(char *str, int c)
{
	int	i;
	int	quote_counter;
	
	i = 0;
	quote_counter = 0;
	while (i <= c)
	{
		if (str[i] == '\'')
			quote_counter++;
		i++;
	}
	if (quote_counter % 2 == 0)
		return (true);
	else
		return (false);
}

bool	is_token_delimiter(char character, char *str, int c)
{
	if (character == '|' || (character == '<' && str[c + 1] == '<'))
		return (true);
	else if (character == '$')
		return (check_dollar(str, c));
	else
		return (false);
}

t_token_struct	*get_delimiter_token(char *c)
{
	t_token_struct	*token;
	int 			nbr;
	
	token = (t_token_struct *)malloc(sizeof(t_token_struct));
	if (!token)
		return (NULL);
	if (c[0] == '|')
		token->e_token_type = PIPE;
	else if (c[0] == '<' && c[1] == '<')
		token->e_token_type = DGREAT;
	if (c[1] == '<')
		nbr = 3;
	else
		nbr = 2;
	token->token = (char *)malloc(sizeof(char) * nbr);
	if (!token->token)
		return (NULL);
	token->token[0] = c[0];
	if (c[1] == '<')
		token->token[1] = c[1];
	token->token[nbr - 1] = '\0';
	return (token);
}

t_token_struct	*get_token(int start, int stop, char *input)
{
	t_token_struct	*token;

	token = (t_token_struct *)malloc(sizeof(t_token_struct));
	if (!token)
		return (NULL);
	token->e_token_type = WORD;
	if (input[start] == '<')
		start++;
	token->token = ft_substr(input, start, (stop - start));
	return (token);
}

t_token_struct	**parse_tokens(char *input)
{
	t_token_struct	**token;
	int				token_nbr;
	int				start;
	int				c;

	c = 0;
	start = 0;
	token_nbr = 0;
	token = (t_token_struct **)malloc(sizeof(t_token_struct *) * 20);
	while (input[c] != '\0')
	{
		if (is_token_delimiter(input[c], input, c))
		{
			token[token_nbr] = get_token(start, c, input);
			token[token_nbr]->nbr_from_left = token_nbr;
			token_nbr++;
			token[token_nbr] = get_delimiter_token(input + c);
			token[token_nbr]->nbr_from_left = token_nbr;
			token_nbr++;
			start = c + 1;
			while (input[start] == ' ')
				start ++;
		}
		c++;
	}
	token[token_nbr] = get_token(start, c, input);
	token[token_nbr]->nbr_from_left = token_nbr;
	token[token_nbr + 1] = NULL;
	for (int i = 0; token[i] != NULL; i++)
		printf("TOKEN %d TOKEN-NBR: %d STRING: %s TOKEN-TYPE %u\n", i, token[i]->nbr_from_left, token[i]->token, token[i]->e_token_type);
	return (token);
}

char	*get_cmd(char *word)
{
	char	**arr;
	char	*cmd;

	arr = ft_split(word, ' ');
	cmd = ft_strdup(arr[0]);
	free_array(arr);
	return (cmd);
}

char	*get_args(char *word)
{
	char	*arg;
	char	**arr;

	arr = ft_split(word, ' ');
	if (arr[1] == NULL)
		return (NULL);
	arg = ft_strdup(word + ft_strlen(arr[0]) + 1);
	free_array(arr);
	return (arg);
}

t_token_struct	*split_words(t_token_struct *token)
{
	t_token_struct	*new_token;

	new_token = (t_token_struct *)malloc(sizeof(t_token_struct));
	new_token->cmd = get_cmd(token->token);
	new_token->args = get_args(token->token);
	free(token);
	return (new_token);
}

bool	has_here_doc(t_token_struct **tokens)
{
	int	i;

	i = 0;
	while(tokens[i] != NULL)
	{
		if (tokens[i]->e_token_type == DGREAT)
			return (true);
		i++;
	}
	return (false);
}

void	parse_input(char *input)
{
	t_token_struct	**tokens;
	int				i;

	tokens = parse_tokens(input);
	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->e_token_type == WORD)
			tokens[i] = split_words(tokens[i]);
		i++;
	}
	// if (has_here_doc(tokens))
	// 	execute_here_doc();
	// else
	// 	excute_left_right();
	for (int i = 0; tokens[i] != NULL; i++)
		printf("TOKEN: %s CMD: %s ARGS: %s\n", tokens[i]->token, tokens[i]->cmd, tokens[i]->args);
}