/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:26:31 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/23 11:33:16 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token
{
	DLESS,
	PIPE,
	DOLLAR,
	DGREAT,
	LESS,
	GREAT,
	WORD,
}	t_token;

typedef struct s_token
{
	char			*token;
	t_token			e_token_type;
	int				nbr_from_left;
	int				layer;
}	t_token_struct;

typedef struct s_tree {
	struct s_tree	*root;
	struct s_token	*token;
	struct s_tree	*right;
	struct s_tree	*left;	
}	t_tree;

int		get_arr_words(char *input);
int		get_len_normal(char *source);
int		get_len_quotes(char *source);
char	**split_cmds(char *input, int *argc);

bool			check_dollar(char *str, int c);
bool			is_token_delimiter(char character, char *str, int c);
t_token_struct	*get_token(int start, int stop, char *input);
t_token_struct	**parse_tokens(char *input);

#endif