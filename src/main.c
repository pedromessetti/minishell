/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:11:30 by pedro             #+#    #+#             */
/*   Updated: 2023/08/25 11:55:08 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	has_variable(char *buf)
// {
// 	if (ft_strnstr(buf, "$", ft_strlen(buf)))
// 		return (1);
// 	return (0);
// }

// int	valid_variable(char *buf, char **envp)
// {
// 	char	*var;

// 	if (((var = ft_strnstr(buf, "$", ft_strlen(buf)))))
// 	{
// 		if (!handle_variable(var, envp))
// 			return (0);
// 	}
// 	return (1);
// }

// int	calc_len(char *s)
// {
// 	int	i;

// 	i = -1;
// 	while (s[++i])
// 	{
// 		if (s[i] == '=')
// 			break ;
// 	}
// 	return (i);
// }

// char	*handle_variable(char *var, char **envp)
// {
// 	int	i;

// 	i = -1;
// 	++var;
// 	while (envp[++i])
// 	{
// 		if (ft_strncmp(envp[i], var, calc_len(envp[i])) == 0)
// 			return (ft_strchr(envp[i], '='));
// 	}
// 	return (NULL);
// }

// void is_input(char *input){
// 	char *ocurr = NULL;
// 	if ((ocurr = ft_strnstr(input, "<", ft_strlen(input))))
// 	{
// 		++ocurr;
// 		if (ft_isspace(*ocurr))
// 			++ocurr;
// 		char **tmp = ft_split(ocurr, ' ');
// 		int infile = open(tmp[0], O_RDONLY);
// 		if (infile == -1)
// 		{
// 			ft_printf(RED "minishell: ");
// 			perror(tmp[0]);
// 			ft_printf(RESET);
// 		}
// 		else
// 			printf("file opened\n");
// 		free_matrix(tmp);
// 	}
// }

// void	handle_arg(char *input, char **envp)
// {
// 	char	**args;
// 	t_cmd_tb	*list;

// 	list = NULL;
// 	if (!input[0] || ft_str_isspace(input) || (has_variable(input) && !valid_variable(input, envp)))
// 		return ;
// 	if (has_redirections(input)) {
// 		is_input(input);
// 	}
// 	if (has_pipe(input))
// 	{
// 		args = ft_split(input, '|');
// 		list = define_multiple_path(list, args, envp);
// 		start_process(list, envp);
// 		free_matrix(args);
// 		free_path_list(&list);
// 	}
// 	else
// 	{
// 		list = define_path(list, input, envp);
// 		list->pid = fork();
// 		if (list->pid == 0)
// 		{
// 			if (ask_for_exit_status(list->args))
// 				exit(g_last_exit_status);
// 			child_process(list, envp);
// 		}
// 		waitpid(list->pid, &g_last_exit_status, 0);
// 		free_path_list(&list);
// 	}
// }

#define TOKEN_IDENTIFIER 0 		// commands, program name and other user-defined (ex: ls, ./minishell)
#define TOKEN_OPERATOR 1			// operators	(ex: |, <, >)
#define TOKEN_LITERAL 2				// literals strings (ex: "hello 123")
#define TOKEN_ENV_VARIABLE 3	// environment variables (ex: $PATH)
#define TOKEN_ARG 4						// arguments (ex: ls -l)

int	identify_token_type(char *str, int len)
{
	// Check if the string is an identifier
	if (ft_isalpha(str[0]))
		return (TOKEN_IDENTIFIER);
	// Check if the string is an operator
	if (len == 1 && ft_strchr("|<>", str[0]))
		return (TOKEN_OPERATOR);
	// Check if the string is a literal
	if (ft_isnum(str[0])) // Implement logic for parsing strings inside quotes
		return (TOKEN_LITERAL);
	// Check if the string is an environment variable
	if (str[0] == '$')
		return (TOKEN_ENV_VARIABLE);
	// Check if the string is an argument
	if (ft_isprint(str[0]))
		return (TOKEN_ARG);
	// If doesn't satisfy any tokens, return an error
	return (-1);
}

void	create_token(t_token *token, int type, char *str, int len)
{
	token->type = type;
	ft_strncpy(token->content, str, len);
	token->content[len] = '\0';
}

void	lexical_analysis(char *prompt)
{
	int	token_count;
	int	i;
	int	start;
	int	end;
	int	type;

	t_token tokens[100]; // Ajustar tamanho depois
	token_count = 0;
	i = 0;
	while (prompt[i])
	{
		// Skip whitespaces
		if (ft_isspace(prompt[i]))
			i++;
		// Identify token boundaries
		start = i;
		end = start;
		while (prompt[end] && !ft_isspace(prompt[end]))
			end++;
		// Identify and create tokens
		type = identify_token_type(prompt + start, end - start);
		create_token(tokens + token_count, type, prompt + start, end - start);
		token_count++;
		// Move to next token
		i = end;
	}
	// Print the extracted tokens
	for (int j = 0; j < token_count; j++)
	{
		printf("Token Type: %d, Content: %s\n", tokens[j].type,
				tokens[j].content);
	}
}

void	init(char **envp)
{
	char	*prompt;

	(void)envp;
	while (1)
	{
		prompt = readline(WHITE "minishell> " RESET);
		add_history(prompt);
		if (ft_strncmp(prompt, "exit", ft_strlen(prompt)) == 0)
		{
			free(prompt);
			exit(EXIT_SUCCESS);
		}
		lexical_analysis(prompt);
		free(prompt);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	check_ac(ac);
	init(envp);
	return (0);
}
