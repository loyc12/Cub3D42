#------------------------------------------------------------------------------#
#                                   COLOURS                                    #
#------------------------------------------------------------------------------#

DEF_COLOR = \033[0;39m
NC		= \e[0;39m
MAGENTA	= \033[0;95m
LMAGENTA = \e[95m
RED		= \033[0;91m
LRED	= \e[91m
YELLOW	= \033[0;93m
LYELLOW	= \e[93
GREEN	= \033[0;92m
LGREEN	= \e[92m
CYAN	= \033[0;96m
LCYAN	= \e[96m
BLUE	= \033[0;94m
GRAY	= \033[0;90m
WHITE	= \033[0;97m

#------------------------------------------------------------------------------#
#                                   GENERICS                                   #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all ldirs bonus clean fclean clear fclear re run rerun leaks releaks display

#------------------------------------------------------------------------------#
#                                    FLAGS                                     #
#------------------------------------------------------------------------------#

CFLAGS	=	-Wall -Werror -Wextra $(XFLAGS)

# Set to @ to disable enable echoing cmd calls:
HIDE	=	@

# Extra flags
# Use "export XFLAGS=..." to add extra compilation flags,
# -g					for debug mode
# -fsanitize=thread		to see race conditions

#------------------------------------------------------------------------------#
#                                  VARIABLES                                   #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
RM		=	rm -rf
MD		=	mkdir -p
INCLUDE =	-I include

# Program and directory names
NAME	=	philo
SRCDIR	=	src/
OBJDIR	=	bin/
TSTDIR	=	tests/

# File names (including their subdirectory if needed)
FILES	=	main \

# Libraries (.a files) to include for compilation
LIBFT	=
LIBRL	=

SRCS	=	$(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))

# Default command to call when using make run or make leaks
CMD		=	./cub3D ./maps/test_map_1.cub
#------------------------------------------------------------------------------#
#                                   TARGETS                                    #
#------------------------------------------------------------------------------#

all: ldirs $(NAME)

# Creates the object directories and subdirectories
ldirs:
	$(HIDE) $(MD) $(OBJDIR)

# Compiles files into executable
$(NAME): $(OBJS)
	$(HIDE) $(START)
	$(HIDE) $(CC) $(MODE) $(CFLAGS) $(INCLUDE) $(LIBFT) -o $@ $^ $(LIBRL)
	@echo "$(GREEN)Files compiled with flags : $(CFLAGS)$(DEF_COLOR)"

$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	$(HIDE) $(CC) $(MODE) $(CFLAGS) -c $< -o $@ $(INCLUDE)

# Removes objects
clear: clean
clean:
	$(HIDE) $(RM) $(OBJS)
	$(HIDE) $(RM) $(NAME).dSYM
	@echo "$(MAGENTA)Object files cleaned$(DEF_COLOR)"

# Removes object dir and executable
fclear: fclean
fclean: clean
	$(HIDE) $(RM) $(OBJDIR)
	@echo "$(MAGENTA)Object directory cleaned$(DEF_COLOR)"
	$(HIDE) $(RM) $(NAME)
	@echo "$(RED)Executable cleaned$(DEF_COLOR)"

# Removes object dir and executable and remakes everything
re: fclean all
	@echo "$(CYAN)Cleaned and rebuilt everything!$(DEF_COLOR)"

# Runs the program
rerun: re run
run: all
	$(HIDE) $(CMD)

# Runs the program with valgrind
releaks: re leaks
leaks: all
	@echo "$(RED)Checking leaks...$(DEF_COLOR)"
	$(HIDE) valgrind --show-leak-kinds=all --trace-children=yes --leak-check=full --track-fds=yes --suppressions=include/supp $(CMD)

# Display start screen
display:
	$(HIDE) $(START)
