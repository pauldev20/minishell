/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:26:31 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/21 12:09:47 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token
{
	DLESS,
	PIPE,
	DGREAT,
	LESS,
	GREAT,
	WORD,
}	t_token;


typedef struct s_cmd
{
	char			*cmd;
	t_token			e_token;
	bool			is_root;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char			*token;
	t_token			e_token_type;
	int				nbr_from_left;
	bool			is_prio;
}	t_token_struct;

typedef struct s_tree {
	struct s_tree	*root;
	struct s_cmd	*cmd;
	struct s_tree	*right;
	struct s_tree	*left;	
} t_tree;
 
int		get_arr_words(char *input);
int		get_len_normal(char *source);
int		get_len_quotes(char *source);
char	**split_cmds(char *input, int *argc);

t_cmd	*init_token(char *arr, t_cmd *head);
t_cmd	*ft_cmdnew(char *command, t_token token);

bool	is_delimiter(t_token i);

#endif