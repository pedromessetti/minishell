/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:26:50 by annamarianu       #+#    #+#             */
/*   Updated: 2023/09/07 11:36:14 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_cd(const char *directory) {
    if (!*directory){
        chdir(ft_getenv("HOME"));
    }
    else
    {
        if(chdir(directory) != 0 ) 
            perror("minishell: cd");
    }
}

void execute_echo(const char **args) {
    int i = 0;
    int add_newline = 1;

    if (args[i] != NULL && ft_strcmp(args[i], "-n") == 0) 
    {
        add_newline = 0;
        i++;
    }
    while (args[i] != NULL) 
    {
        const char *arg = args[i];
        char *trimmed_arg = ft_strtrim(arg, "\"");
        printf("%s", trimmed_arg);
        free(trimmed_arg);
        i++;
        if (args[i] != NULL) {
            printf(" ");
        }
    }
    if (add_newline) {
        printf("\n");
    }
}

int execute_identifier(t_token *tokens, int token_count, char **envp, int start, t_cmd_tb **cmd_list) 
{
    int i = start;
    while (i < token_count) {
        if (tokens[i].type == TOKEN_IDENTIFIER || tokens[i].type == TOKEN_KEYWORD) {
            int args_count = 1;
            int k = 0;
            while (tokens[i + k + 1].type == TOKEN_ARG || tokens[i + k + 1].type == TOKEN_LITERAL) {
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
            ft_strcmp(tokens[i + args_count + 1].content, "|") == 0) 
          	{
                i += args_count + 2;
                continue;
            }
        }
        i++;
    }
    return i;
}

int parse(t_token *tokens, int token_count, char **envp)
 {
    t_cmd_tb *cmd_list = NULL;
    int i = 0;

    while (i < token_count) 
    {
        if (ft_strcmp(tokens[i].content, "cd") == 0)
        {
            i++;
            if (ft_strcmp(tokens[i+1].content, "|") == 0)
                i++;
            else if (ft_strcmp(tokens[i].content, "|") == 0)
                continue;
            else
                execute_cd(tokens[i].content);
        }
        // else if (ft_strncmp(tokens[i].content, "unset", 5) == 0)
        // {
        //     i++;
        //     while (i < token_count && tokens[i].type == TOKEN_ARG) 
        //     {
        //         unsetenv(tokens[i].content);
        //         i++;
        //     }
        // }
        // else if (ft_strncmp(tokens[i].content, "export", 6) == 0) 
        // {
        //     i++;
        //     while (i < token_count && tokens[i].type == TOKEN_ARG) 
        //     {
        //         char *env_var = ft_strdup(tokens[i].content);
        //         char *env_var_value = ft_strchr(env_var, '=');
        //         if (env_var_value) 
        //         {
        //             *env_var_value = '\0';
        //             env_var_value++;
        //             setenv(env_var, env_var_value, 1);
        //         }
        //         else 
        //         {
        //             setenv(env_var, "", 1);
        //         }
        //         free(env_var);
        //         i++;
        //     }
        // }
        else if (ft_strncmp(tokens[i].content, "env", 3) == 0) 
        {
            int fd = open(".env", O_RDONLY);
            // printf(":%s:\n", tokens[i+1].content);
            if (tokens[i+1].content) {
                char *line = get_next_line(fd);
                while (line) 
                {
                    printf("%s", line);
                    line = get_next_line(fd);
                }
            }
            close(fd);
            i++;
        }
        else if (tokens[i].type == TOKEN_KEYWORD && strcmp(tokens[i].content, "echo") == 0) 
        {
            i++;
            const char **echo_args = (const char **)malloc((token_count - i + 1) * sizeof(const char *));
            int arg_index = 0;
            if (!echo_args)
                return -1;
            while (i < token_count) 
            {
                if (tokens[i].type == TOKEN_OPERATOR && strcmp(tokens[i].content, "|") == 0) 
                    break; 
                echo_args[arg_index] = tokens[i].content;
                arg_index++;
                i++;
            }
            echo_args[arg_index] = NULL;
            execute_echo(echo_args);
            free(echo_args);
        } 
        else if (tokens[i].type == TOKEN_IDENTIFIER)
            i = execute_identifier(tokens, token_count, envp, i, &cmd_list);
        else if (tokens[i].type == TOKEN_OPERATOR && ft_strcmp(tokens[i].content, "|") == 0) 
        {
            i++;
            continue;
        }
        i++;
    }
    start_process(cmd_list, envp);
    free_path_list(&cmd_list);
    return 0;
}

// int parse_key_literal(t_token *tokens, int token_count, char **envp, int start, t_cmd_tb **cmd_list) 
// {
//     int i = start;
//     while (i < token_count) {
//         if (tokens[i].type == TOKEN_KEYWORD) {
//             if (ft_strcmp(tokens[i].content, "echo") == 0) {
// 				printf("Encontrou comando echo\n");
//                 int args_count = 0;
//                 int j = 1;
//                 while (i + j < token_count && tokens[i + j].type == TOKEN_LITERAL) {
//                     args_count++;
//                     j++;
//                 }
//                 char **args = (char **)malloc((args_count + 2) * sizeof(char *));
//                 if (!args)
//                     return -1;
//                 args[0] = ft_strdup(tokens[i].content); 
//                 int current_arg = 0;
//                 j = 1;
//                 while (i + j < token_count && tokens[i + j].type == TOKEN_LITERAL) {
//                     args[current_arg + 1] = ft_strtrim(tokens[i + j].content, "\"");
//                     current_arg++;
//                     j++;
//                 }
//                 args[current_arg + 1] = NULL; 
// 				printf("Comando antes de ser adicionado à lista:\n");
				
//                 *cmd_list = choose_handle(args[0], envp, *cmd_list, args);
				
//                 if (i + j < token_count && tokens[i + j].type == TOKEN_OPERATOR &&
//                     ft_strcmp(tokens[i + j].content, "|") == 0) {
//                     printf("Encontrou operador |\n");
// 					// Retorne o valor de i apenas quando encontrar um operador |
//                     return i + j;
//                 }
//             }
//         }
//         i++;
//     }
//     // Retorne i quando terminar a análise
//     return i;
// }



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