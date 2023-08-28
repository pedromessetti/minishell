#include "minishell.h"

// Tests for Lexical Analysis
int	main(void) {
	char *test_1 = "cat < Makefile | ls -l | grep inc | echo 'how are you?' > file.txt | exit";
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

	// To be implemented
	// char *test_ = "'single quoted'"; // has to be interpreted as a identifier
	// char *test_ = "\"double quoted\""; // has to be interpreted as a identifier
	// char *test_ = "-l"; // has to be interpreted as a identifier
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
	lex(test_1);
	printf("\n%s\n", test_2);
	lex(test_2);
	printf("\n%s\n", test_3);
	lex(test_3);
	printf("\n%s\n", test_4);
	lex(test_4);
	printf("\n%s\n", test_5);
	lex(test_5);
	printf("\n%s\n", test_6);
	lex(test_6);
	printf("\n%s\n", test_7);
	lex(test_7);
	printf("\n%s\n", test_8);
	lex(test_8);
	printf("\n%s\n", test_9);
	lex(test_9);
	printf("\n%s\n", test_10);
	lex(test_10);
	printf("\n%s\n", test_11);
	lex(test_11);
	printf("\n%s\n", test_12);
	lex(test_12);
	return (0);
}
