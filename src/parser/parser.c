/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/09/22 11:26:47 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"


/* TODO: implement here_docs into lexer
   check quotation before expander maybe?
   do tokenization before parser
   create parsing tree
   parser need to update tokens depending on the token he parses in the moment 
   so he need to look back at the tokenization process and needs to update tokens
   or depending on the last token parsed we can decide which token to handover next
   and also check already if an error in the syntax has occured (e.g. "|||" or sth like "<< |")
   also return if we finished parsing a cmd_with_args and then move over to the second part
   of the pipe if we have end of input
   1. Check for io_modifiern
   2. redircet io if nesecary
   3. create tokengroups into cmd_and_args
   4. make syntax tree of pipes
   5. execute syntax tree
*/
typedef struct s_cmd {
	char	**full_cmd;
	char	*full_path;
	int		infd;
	int		outfd;
}	t_cmd;

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->full_cmd = NULL;
	cmd->full_path = NULL;
	cmd->infd = STDIN_FILENO;
	cmd->outfd = STDOUT_FILENO;
	return (cmd);
}

void	*parse_input(char *input)
{
	char	**splitted;
	int		c;
	
	splitted = lexer(input, ' ');
	if (!splitted)
		return (print_error(QUOTE, NULL, 1));
	pipe_expander(&splitted);
	c = 0;
	while (splitted[c] != NULL)
	{
		splitted[c] = expand_vars(splitted[c]);
		c++;
	}
	printf("{");
	for (int i = 0; splitted[i] != NULL; i++)
		printf("%s, ", splitted[i]);
	printf("NULL}\n");
	// execute(splitted);
	for (int i = 0; splitted[i] != NULL; i++)
		free(splitted[i]);
	free(splitted);
	return (NULL);
}
