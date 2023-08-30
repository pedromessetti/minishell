/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:26:50 by annamarianu       #+#    #+#             */
/*   Updated: 2023/08/30 21:16:45 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse(t_token *tokens, int token_count, char **envp) {
    t_cmd_tb *cmd_list = NULL;
    int i = 0;

    while (i < token_count) {
        if (tokens[i].type == TOKEN_IDENTIFIER) {
            i = parse_ident_arg(tokens, token_count, envp, i, &cmd_list);
        } else if (tokens[i].type == TOKEN_KEYWORD) {
            if (strcmp(tokens[i].content, "echo") == 0) {
                i = parse_key_literal(tokens, token_count, envp, i, &cmd_list);
            }
        }
        i++;
    }

    start_process(cmd_list, envp);
    free_path_list(&cmd_list);
    return 0;
}



int parse_ident_arg(t_token *tokens, int token_count, char **envp, int start, t_cmd_tb **cmd_list) 
{
    int i = start;
    while (i < token_count) {
        if (tokens[i].type == TOKEN_IDENTIFIER) {
            int args_count = 1;
            int k = 0;
            while (tokens[i + k + 1].type == TOKEN_ARG) {
                k++;
                args_count++;
            }
            char **args = (char **)malloc((args_count + 1) * sizeof(char *));
            if (!args)
                return -1;
            args[0] = ft_strdup(tokens[i].content);
            int j = 1;
            while (j <= args_count) {
                args[j] = ft_strdup(tokens[i + j].content);
                j++;
            }
            args[args_count] = NULL;

            *cmd_list = choose_handle(args[0], envp, *cmd_list, args);

            if (tokens[i + args_count + 1].type == TOKEN_OPERATOR &&
                ft_strcmp(tokens[i + args_count].content, "|") == 0) {
                i += args_count + 1;
                continue;
            }
        }
        i++;
    }
    return i;
}

int parse_key_literal(t_token *tokens, int token_count, char **envp, int start, t_cmd_tb **cmd_list) 
{
    int i = start;
    while (i < token_count) {
        if (tokens[i].type == TOKEN_KEYWORD) {
            if (strcmp(tokens[i].content, "echo") == 0) {
                int args_count = 1;
                int k = 0;
                while (tokens[i + k + 1].type == TOKEN_LITERAL) {
                    k++;
                    args_count++;
                }
                char **args = (char **)malloc((args_count + 1) * sizeof(char *));
                if (!args)
                    return -1;
                args[0] = ft_strdup(tokens[i].content);
                int j = 1;
                while (j <= args_count) {
                    args[j] = ft_strtrim(tokens[i + j].content, "\"");
                    j++;
                }
                args[args_count] = NULL;

                *cmd_list = choose_handle(args[0], envp, *cmd_list, args);

                if (tokens[i + args_count + 1].type == TOKEN_OPERATOR &&
                    ft_strcmp(tokens[i + args_count].content, "|") == 0) {
                    i += args_count + 1;
                    continue;
                }
            }
        }
        i++;
    }
    return i;
}



// int	parser(t_token *tokens, int token_count, char **envp)
// {
// 	t_cmd_tb *cmd_list = NULL;
// 	char **args = NULL;
// 	int i = 0;
// 	while (i < token_count)
// 	{
// 		if (tokens[i].type == TOKEN_IDENTIFIER)
// 		{
// 			int args_count = 1;
//          int k = 0;
// 			while (tokens[i + k + 1].type == TOKEN_ARG)
//          {
//             k++;
// 				args_count++;
//          }
// 			args = (char **)malloc((args_count + 1) * sizeof(char *));
// 			if (!args)
// 				return (-1);
//          args[0] = ft_strdup(tokens[i].content);
// 			int j = 1;
// 			while (j <= args_count)
// 			{
//             args[j] = ft_strdup(tokens[i + j].content);
// 				j++;
// 			}
// 			args[args_count] = NULL;
// 			if (tokens[i].type == TOKEN_IDENTIFIER)
// 				cmd_list = choose_handle(tokens[i].content, envp, cmd_list, args);
         
// 			if (tokens[i + args_count + 1].type == TOKEN_OPERATOR
// 				&& ft_strcmp(tokens[i + args_count].content, "|") == 0)
// 			{
// 				i += args_count + 1; // Skip pipe operator
// 				continue ;           
// 			}
// 		}
// 		i++;
// 	}
//    start_process(cmd_list, envp);
//    free_path_list(&cmd_list);
// 	return (0);
// }

// int	parser_key_literal(t_token *tokens, int token_count, char **envp)
// {
// 	t_cmd_tb *cmd_list = NULL;
// 	char **args = NULL;
// 	int i = 0;
// 	while (i < token_count)
// 	{
// 		if (tokens[i].type == TOKEN_KEYWORD)
// 		{
// 			if (strcmp(tokens[i].content, "echo") == 0)
// 			{
// 				int args_count = 1;
// 				int k = 0;
// 				while (tokens[i + k + 1].type == TOKEN_LITERAL)
// 				{
// 					k++;
// 					args_count++;
// 				}
// 				args = (char **)malloc((args_count + 1) * sizeof(char *));
// 				if (!args)
// 					return (-1);
// 				args[0] = ft_strdup(tokens[i].content);

// 				int j = 1; // Começa a partir de 1 para os argumentos
// 				while (j <= args_count)
// 				{
// 					args[j] = ft_strtrim(tokens[i + j].content, "\"");
// 					j++;
// 				}
// 				args[args_count] = NULL;

// 				cmd_list = choose_handle(args[0], envp, cmd_list, args);

// 				if (tokens[i + args_count + 1].type == TOKEN_OPERATOR
// 					&& ft_strcmp(tokens[i + args_count].content, "|") == 0)
// 				{
// 					i += args_count + 1;
// 					continue;
// 				}
// 			}
// 		}
// 		i++;

// 	}
//    	start_process(cmd_list, envp);
//    	free_path_list(&cmd_list);
// 	return (0);
// }