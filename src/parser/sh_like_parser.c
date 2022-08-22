/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_like_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:00:53 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/22 17:35:23 by mhedtman         ###   ########.fr       */
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
			while (input[start] == ' ' && input[start] != '\0')
				start ++;
		}
		c++;
	}
	token[token_nbr] = get_token(start, c, input);
	token[token_nbr]->nbr_from_left = token_nbr;
	token[token_nbr + 1] = NULL;
	return (token);
}

void	parse_input(char *input)
{
	t_token_struct	**tokens;
	
	tokens = parse_tokens(input);
	// for (int i = 0; tokens[i] != NULL; i++)
	// {
	// 	write (1, tokens[i]->token, ft_strlen(tokens[i]->token));
	// 	write (1, &tokens[i]->e_token_type, 1);
	// 	write (1, "\n", 1);
	// }
	// get_tree(tokens);
}