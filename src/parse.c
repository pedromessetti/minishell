/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:26:50 by annamarianu       #+#    #+#             */
/*   Updated: 2023/08/30 16:11:30 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_token *tokens, int token_count, char **envp)
{
	t_cmd_tb *cmd_list = NULL;
	char **args = NULL;
	int i = 0;
	while (i < token_count)
	{
		if (tokens[i].type == TOKEN_IDENTIFIER)
		{
			int args_count = 1;
         int k = 0;
			while (tokens[i + k + 1].type == TOKEN_ARG)
         {
            k++;
				args_count++;
         }
			args = (char **)malloc((args_count + 1) * sizeof(char *));
			if (!args)
				return (-1);
         args[0] = ft_strdup(tokens[i].content);
			int j = 1;
			while (j <= args_count)
			{
            args[j] = ft_strdup(tokens[i + j].content);
				j++;
			}
			args[args_count] = NULL;
			if (tokens[i].type == TOKEN_IDENTIFIER)
				cmd_list = choose_handle(tokens[i].content, envp, cmd_list, args);
         
			if (tokens[i + args_count + 1].type == TOKEN_OPERATOR
				&& ft_strcmp(tokens[i + args_count].content, "|") == 0)
			{
				i += args_count + 1; // Skip pipe operator
				continue ;           
			}
		}
		i++;
	}
   start_process(cmd_list, envp);
   free_path_list(&cmd_list);
	return (0);
}