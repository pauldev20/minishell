/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 11:17:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/21 10:04:52 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_cmd	*last_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	append_cmd(t_cmd **lst, t_cmd *cmd)
{
	if (!lst || !cmd)
		return ;
	if (!(*lst))
		*lst = cmd;
	else
	{
		last_cmd(*lst)->next = cmd;
	}
}

t_cmd	*ft_cmdnew(char *command, t_token token)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = command;
	cmd->e_token = token;
	return (cmd);
}

t_cmd	*init_token(char *arr, t_cmd *head)
{
	t_cmd	*cmd;
	t_token	token;

	if (*arr == '<' && *(arr + 1) == '<')
		token = DLESS;
	else if (*arr == '<' && *(arr + 1) == '\0')
		token = LESS;
	else if (*arr == '>' && *(arr + 1) == '\0')
		token = GREAT;
	else if (*arr == '>' && *(arr + 1) == '>')
		token = DGREAT;
	else if (*arr == '|' && *(arr + 1) == '\0')
		token = PIPE;
	else
		token = WORD;
	cmd = ft_cmdnew(arr, token);
	append_cmd(&head, cmd);
	return (head);
}
