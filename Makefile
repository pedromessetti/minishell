.SILENT:

# Color variables
RED = \033[1;31m
GREEN = \033[1;32m
WHITE = \033[1;37m
RESET = \033[0m

# Executable name
NAME = minishell

# Compiler options
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I inc -fsanitize=address

# Source and object files
SRCS =  src/checks.c src/child_process.c src/cmd_tb.c src/env.c src/lex.c src/main.c src/parser.c src/path.c src/tokens.c src/lex_utils.c src/exec.c src/sig.c src/env_utils.c src/cmd_std.c src/redirections.c src/expand.c src/expand_utils.c src/tokens_utils.c src/utils.c

OBJS = $(SRCS:.c=.o)

# Default target
$(NAME):	$(OBJS)
	if [ ! -f ./libft/libft.a ]; then \
		$(MAKE) run -C ./libft/; \
	fi
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME) -lreadline
	echo "$(GREEN)[OK] $(WHITE)$(NAME)$(RESET)" 

# Build minishell executable
all:	$(NAME)

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and the executable
fclean: clean
	rm -f $(NAME)

# Rebuild the project
re: fclean $(NAME)

# Rebuild the project and remove object files
run: re
	$(MAKE) clean
	clear
	./$(NAME)

# Show help message
help:
	echo "\\nUsage: make [target]"
	echo ""
	echo "Targets:"
	echo "  all        Build executable"
	echo "  clean      Remove object files"
	echo "  fclean     Remove object files and executable"
	echo "  re         Rebuild project"
	echo "  run        Rebuild project and remove object files"