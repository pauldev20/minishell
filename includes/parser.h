/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:26:31 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/19 14:59:24 by mhedtman         ###   ########.fr       */
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
	struct s_cmd	*next;
}	t_cmd;

int		get_arr_words(char *input);
int		get_len_normal(char *source);
int		get_len_quotes(char *source);
char	**split_cmds(char *input, int *argc);

t_cmd	*init_token(char *arr, t_cmd *head);
t_cmd	*ft_cmdnew(char *command, t_token token);

#endif