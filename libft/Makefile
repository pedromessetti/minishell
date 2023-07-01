.SILENT:

# Color variables for terminal output
RED = \033[1;31m
GREEN = \033[1;32m
WHITE = \033[1;37m
RESET = \033[0m

# Library name
NAME = libft.a

# Create library
CME = ar -rcs

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g -I inc

# Source and object files
SRCS =	$(wildcard ./src/*.c)
OBJS = $(SRCS:.c=.o)

# Default target
$(NAME):	$(OBJS)
	$(CME) $(NAME) $(OBJS)
	echo "$(GREEN)[OK] $(WHITE)$(NAME)$(RESET)" 

# Build library
all:	$(NAME)

# Remove object files
clean:
	rm -f $(OBJS)

# Remove object files and library
fclean:	clean
	rm -f $(NAME) 

# Rebuild library
re:	fclean all

# Rebuild library and remove object files
run: re 
	$(MAKE) clean

# Show help message
help:
	echo "\\nUsage: make [target]"
	echo ""
	echo "Targets:"
	echo "  all        Build library"
	echo "  clean      Remove object files"
	echo "  fclean     Remove object files and $(NAME)"
	echo "  re         Rebuild library"
	echo "  run        Rebuild library and remove object files"

.PHONY: all clean fclean re