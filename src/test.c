// I know that is ugly but I will improve		:p

#include "minishell.h"

// Tests for Lexical Analysis
int	main(int ac, char **av, char **envp) {
	(void)ac;
	(void)av;
	char *test_1 = "cat -e < Makefile | ls -l -a | grep inc | echo 'how are you?' > file.txt | exit";
	char *test_2 = "cd | export | unset | echo | env | pwd";
	char *test_3 = "$PATH | $HOME | $SHELL";
	char *test_4 = "@invalid";
	char *test_5 = "|invalid|";
	char *test_6 = "< /libft/inc/libt.h";
	char *test_7 = "cat < Makefile";
	char *test_8 = "123 | abc | 456";
	char *test_9 = "echo\t\"Hello,\tworld!\"\nls\n";
	char *test_10 = "   echo  \"Hello,  world!\"  ";
	char *test_11 = "echo \"Hello, world!\"";
	char *test_12 = "echo \"Hello, world!\" | cat";
	char *test_13 = "-l";
	char *test_14 = "-l | -l | -a";
	char *test_15 = "cat < Makefile | ls | grep inc | -l | cat";
	char *test_16 = "cat < Makefile | ls | grep inc | -l | cat | -l";
	char *test_17 = "cat < Makefile | ls -l | grep inc | -l | cat -e";
	char *test_18 = "-l | -z -k -y | -a | -c | -x -a";

	// To be implemented
	// char *test_ = "'single quoted'"; // has to be interpreted as a identifier
	// char *test_ = "\"double quoted\""; // has to be interpreted as a identifier
	// char *test_ = "cat <Makefile";
	// char *test_ = "</libft/src/libft.h";
	// char *test_ = "cd /libft/src/";
	// char *test_ = "cd /libft/src/ | ls | grep inc";
	// char *test_ = "mkdir example";
	// char *test_ = "mkdir example.txt";
	// char *test_ = "export VAR=value";
	// char *test_ = ">invalid>";
	// char *test_ = "<invalid<";
	// char *test_ = "invalid|";
	// char *test_ = "invalid>";
	// char *test_ = "invalid<";
	// char *test_ = "invalid$";
	// char *test_ = "invalid@";
	// char *test_ = "-invalid";
	// char *test_ = "$invalid";
	// char *test_ = "invalid|invalid";
	// char *test_ = "invalid|invalid|invalid";
	// char *test_ = "";
	// char *test_ = " ";
	// char *test_ = "grep 'inc src'";

	printf("----- TESTS FOR LEXICAL ANALYSIS -----\n");
	printf("%s\n", test_1);
	lex(test_1, envp);
	printf("\n%s\n", test_2);
	lex(test_2, envp);
	printf("\n%s\n", test_3);
	lex(test_3, envp);
	printf("\n%s\n", test_4);
	lex(test_4, envp);
	printf("\n%s\n", test_5);
	lex(test_5, envp);
	printf("\n%s\n", test_6);
	lex(test_6, envp);
	printf("\n%s\n", test_7);
	lex(test_7, envp);
	printf("\n%s\n", test_8);
	lex(test_8, envp);
	printf("\n%s\n", test_9);
	lex(test_9, envp);
	printf("\n%s\n", test_10);
	lex(test_10, envp);
	printf("\n%s\n", test_11);
	lex(test_11, envp);
	printf("\n%s\n", test_12);
	lex(test_12, envp);
	printf("\n%s\n", test_13);
	lex(test_13, envp);
	printf("\n%s\n", test_14);
	lex(test_14, envp);
	printf("\n%s\n", test_15);
	lex(test_15, envp);
	printf("\n%s\n", test_16);	
	lex(test_16, envp);
	printf("\n%s\n", test_17);
	lex(test_17, envp);
	printf("\n%s\n", test_18);
	lex(test_18, envp);
	return (0);
}
