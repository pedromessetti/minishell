#include "minishell.h"

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
	if (len == 4 && ft_strncmp(str, "echo", 4) == 0) 	// TODO: everything after echo is an literal string and handle echo -n (echo -n "hello")
		return (1);
	if (len == 3 && ft_strncmp(str, "env", 3) == 0)
		return (1);
	if (len == 3 && ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	return 0;
}

int is_identifier(char *str, int len)
{
	//check if is grep
	if (len == 4 && ft_strncmp(str, "grep", 4) == 0)
		return (1);
	if (ft_isalpha(str[0]) || ft_isdir(str))
		return (1);
	return 0;
}

int	identify_token_type(char *str, int len, int *next_token_type, int *echo_flag)
{
	// Check if the string is an argument (if flag is set)
	if (*next_token_type == TOKEN_ARG) {
			*next_token_type = -1; // Reset the flag
			return (TOKEN_FILE);
	}
	// Check if the string is a file (if flag is set)
	if (*next_token_type == TOKEN_FILE) {
			*next_token_type = -1;
			return (TOKEN_IDENTIFIER);
	}
	// Check if the string is a keyword
	if (is_keyword(str, len))
	{
		if (ft_strncmp(str, "echo", 4) == 0)
		{
			*echo_flag = 1; // Set flag for literal string
			return (TOKEN_KEYWORD);
		}
		return (TOKEN_KEYWORD);
	}
	// Check if the string is an identifier
	if (ft_isalnum(str[0]) || ft_isdir(str))
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

int is_redirection(char *str, int len)
{
	if (len == 1 && ft_strchr("<>", str[0]))
		return (1);
	return 0;
}

void	lex(char *prompt)
{
	int	i;
	int	start;
	int	end;
	int	type;
	int token_count = 0;
	int next_token_type = -1;
	int echo_flag = 0;
	t_token tokens[100]; // TODO: implement malloc

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
		type = identify_token_type(prompt + start, end - start, &next_token_type, &echo_flag);
		if (echo_flag && type != TOKEN_OPERATOR && type != TOKEN_KEYWORD)
			type = TOKEN_LITERAL; // Treat as literal string
		else if (type == TOKEN_OPERATOR)
			echo_flag = 0; // Reset flag after finding operator
		if (type == TOKEN_IDENTIFIER && ft_strncmp(prompt + start, "grep", 4) == 0)
			next_token_type = TOKEN_ARG;
		if (type == TOKEN_OPERATOR && is_redirection(prompt + start, end - start))
			next_token_type = TOKEN_FILE;
		create_token(tokens + token_count, type, prompt + start, end - start);
		token_count++;
		// Move to next token
		i = end;
	}
	printf("token_count: %d\n", token_count);
	// Print the extracted tokens
	for (int j = 0; j < token_count; j++)
		printf("token[%d] | type: %d | content: %s\n",j, tokens[j].type, tokens[j].content);
		
	//Pass the tokens to the parser
	// parser(tokens, token_count);
}