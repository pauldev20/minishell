/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:39:42 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/24 14:03:36 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_table(t_ct *cmd_table)
{
	free_array(cmd_table->cmd_array);
	free_array(cmd_table->arg_array[0]);
	free(cmd_table->arg_array);
	free_array(cmd_table->in);
	free_array(cmd_table->in_type);
	free_array(cmd_table->out);
	free_array(cmd_table->out_type);
	free_array(cmd_table->here_docs);
	if (cmd_table != NULL)
		free(cmd_table);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	*free_arr(char **arr, int arr_count)
{
	if (arr != NULL)
	{
		while (arr[arr_count] != NULL && arr_count >= 0)
		{
			free(arr[arr_count]);
			arr_count--;
		}
		free(arr);
	}
	return (NULL);
}
