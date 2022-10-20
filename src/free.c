/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:39:42 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/20 11:42:16 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_table(t_ct *cmd_table)
{
	free_array(cmd_table->cmd_array);
	free_array(cmd_table->in);
	free_array(cmd_table->in_type);
	free_array(cmd_table->out);
	free_array(cmd_table->out_type);
	free_array(cmd_table->here_docs);
	if (cmd_table)
		free(cmd_table);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	*free_arr(char **arr, int arr_count)
{
	while (arr_count >= 0)
		free(arr[arr_count--]);
	free(arr);
	return (NULL);
}