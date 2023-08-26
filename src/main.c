/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 09:11:30 by pedro             #+#    #+#             */
/*   Updated: 2023/08/26 18:06:28 by pedro            ###   ########.fr       */
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

int is_literal_string(char *str, int len)
{
	if (len < 2)
		return 0;
	if ((str[0] == '"' && str[len-1] == '"') || (str[0] == '\'' && str[len-1] == '\''))
		return 1;
	return 0;
}

// Check if the string is a keyword
int is_keyword(char *str, int len)
{
	if (len == 4 && ft_strncmp(str, "exit", 4) == 0)
		return (1);
	if (len == 2 && ft_strncmp(str, "cd", 2) == 0)
		return (1);
	if (len == 6 && ft_strncmp(str, "export", 6) == 0)
		return (1);
	if (len == 5 && ft_strncmp(str, "unset", 5) == 0)
		return (1);
	if (len == 4 && ft_strncmp(str, "echo", 4) == 0) // Td q vier dps até um operator sera considerado literal string
		return (1);																		// lidar com -n
	if (len == 3 && ft_strncmp(str, "env", 3) == 0)
		return (1);
	if (len == 3 && ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	return 0;
}

int	identify_token_type(char *str, int len)
{
	// Check if the string is a keyword
	if (is_keyword(str, len))
		return (TOKEN_KEYWORD);
	// Check if the string is an identifier
	if (ft_isalpha(str[0]) || ft_isdir(str))
		return (TOKEN_IDENTIFIER);
	// Check if the string is an operator
	if (len == 1 && ft_strchr("|<>", str[0]))
		return (TOKEN_OPERATOR);
	// Check if is a literal string (inside quotes)
	if (is_literal_string(str, len))
		return (TOKEN_LITERAL);
	// Check if the string is an environment variable
	if (str[0] == '$')
		return (TOKEN_ENV_VARIABLE);
	// Check if the string is an argument
	if (str[0] == '-')
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

	t_token tokens[100]; // malloc depois
	token_count = 0;
	i = 0;
	while (prompt[i])
	{
		// Skip whitespaces
		if (ft_isspace(prompt[i]))
			i++;
		// Token boundaries
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
		printf("===Token===\nType: %d\nContent: %s\n===========\n", tokens[j].type, tokens[j].content);
		
	//Pass the tokens to the parser
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
