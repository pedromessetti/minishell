/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:26:50 by annamarianu       #+#    #+#             */
/*   Updated: 2023/08/29 11:19:47 by annamarianu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"
 
// char **get_arguments(t_token *tokens, int *start_index, int token_count)
// {
//     int num_args = 0;
//     int i = *start_index;
//     char **args = (char **)malloc((num_args + 1) * sizeof(char *));

//     // Contar o número de argumentos
//     while (i < token_count && tokens[i].type == TOKEN_IDENTIFIER)
//     {
//         num_args++;
//         i++;
//     }   
//     if (!args)
//         return NULL;

//     i = *start_index;
//     int arg_index = 0;

//     // Preencher a matriz de argumentos
//     while (i < token_count && tokens[i].type == TOKEN_IDENTIFIER)
//     {
//         args[arg_index] = strdup(tokens[i].content);
//         if (!args[arg_index])
//         {
//             free_matrix(args);
//             return NULL;
//         }

//         arg_index++;
//         i++;
//     }
//     args[arg_index] = NULL; 
//     *start_index = i; // Atualizar o índice de início para a próxima iteração

//     return args;
// }



 int parser(t_token *tokens, int token_count, char **envp)
 {
 	t_cmd_tb *cmd_list = NULL;
    char **args = NULL;
 	int i = 0;
    int j = 0;
 	while (i < token_count)
 	{
 		if (tokens[i].type == TOKEN_IDENTIFIER)
 		{
            int args_count = 0;
            while(tokens[i + args_count + 1].type == TOKEN_ARG)
               args_count++;
            args = (char **)malloc((args_count + 1) * sizeof(char *));
             if (!args)
                return -1;
            while(j < args_count)
            {
                args[j] = strdup(tokens[i + j + 1].content);
                j++;
            }
            args[args_count] = NULL;
 			// char **possible_paths = set_possible_paths(envp);
            // args = get_arguments(tokens, i, token_count);
            // cmd_list = find_path(cmd_list, possible_paths, tokens[i].content, args);
            cmd_list = choose_handle(tokens[i].content, envp, cmd_list,args);
            // if(cmd_list)
            // {
            //     cmd_list = set_cmd_tb_list(cmd_list, cmd_list->path, args);
            //     free_matrix(args); 
            // }
            // free_matrix(possible_paths);
        }
 		// else if (tokens[i].type == TOKEN_OPERATOR)
 		// {
 		// 	if(strcmp(tokens[i].content,"|") == 0)
        //     {
        //         cmd_list = add_path(NULL, args);
        //         ft_add_tail(&cmd_list, cmd_list);

        //         args = initialize_empty_args();
        //     }
        //     else if(strcmp(tokens[i].content,"<") == 0)
        //     {
        //         //redirect_input(args,tokens[i + 1].content);
        //         //i++;
        //     }
        //     else if(strcmp(tokens[i].content,">") == 0)
        //     {
        //         //redirect_output(args,tokens[i + 1].content);
        //         //i++;
        //     }
 		// }
 		i++;
 	}
 	return (0);
 }