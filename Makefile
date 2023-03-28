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
.PHONY: all ldirs \
		deps bonus \
		clean fclean \
		clear fclear \
		re run rerun \
		leaks releaks \
		brew cmake \

#------------------------------------------------------------------------------#
#                                    FLAGS                                     #
#------------------------------------------------------------------------------#

CFLAGS	=	-Wall -Werror -Wextra $(XFLAGS)

# Comment the line bellow to have verbose cmds:
HIDE	=	@

# Extra flags
# Use "export XFLAGS= {flags} " to add extra compilation flags
# Potential flags to use :
# -g					for debug mode
# -fsanitize=thread		to see race conditions

#------------------------------------------------------------------------------#
#                                  VARIABLES                                   #
#------------------------------------------------------------------------------#

# Compiler, flags and shortcuts
CC		=	gcc
RM		=	rm -rf
MKD		=	mkdir -p
CPY		=	cp -f
INCLUDE =	-I include

# Executable name
NAME	=	cub3D

# Directory names
SRCDIR	=	src/
OBJDIR	=	bin/
TSTDIR	=	tests/
SUBMDS	=	MLX42/ \
			Libft42/ \

# Source file names (prefix their subdir if needed)

FILES	=	main \

# Libraries (.a files) to include for compilation
LIBX	=	-lglfw -L "/Users/$$USER/.brew/opt/glfw/lib/"
LIBS	=	./Libft42/libft.a \
			./MLX42/build/libmlx42.a \

# Creates file paths
SRCS	=	$(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))

# Default command to call when using make run or make leaks
CMD		=	./cub3D ./maps/test_map_1.cub

#------------------------------------------------------------------------------#
#                                   TARGETS                                    #
#------------------------------------------------------------------------------#

all: mkdirs $(NAME)

# Creates the object directory (add subdirs manually?)
mkdirs:
	$(HIDE) $(MKD) $(OBJDIR)

# Compiles files into executable
$(NAME): deps $(OBJS)
	$(HIDE) $(CC) $(MODE) $(CFLAGS) $(INCLUDE) $(LIBS) $(LIBX)
	@echo "$(GREEN)Files compiled with flags : $(CFLAGS)$(DEF_COLOR)"

deps: cmake glfw
	$(HIDE) git submodule init --quiet
	$(HIDE) git submodule update --quiet
	$(HIDE) cd MLX42 && cmake -B build && cmake --build build -j4
	$(HIDE) cd Libft42 && make
	@echo "$(BLUE)Submodules set up$(DEF_COLOR)"


$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	$(HIDE) $(CC) $(MODE) $(CFLAGS) -c $< -o $@ $(INCLUDE)


# Removes objects
clear: clean
clean:
	$(HIDE) $(RM) $(OBJS)
	$(HIDE) $(RM) $(NAME).dSYM
	$(HIDE) cd Libft42 && make clean
	@echo "$(MAGENTA)Object files cleaned$(DEF_COLOR)"

# Removes object dir and executable
fclear: fclean
fclean: clean
	$(HIDE) $(RM) $(OBJDIR)
	@echo "$(MAGENTA)Object directory cleaned$(DEF_COLOR)"
	$(HIDE) $(RM) $(NAME)
	$(HIDE) cd Libft42 && make fclean
	@echo "$(RED)Executable cleaned$(DEF_COLOR)"

xclear: xclean
xclean: fclean
	$(HIDE) git submodule deinit --quiet --all -f
	@echo "$(RED)Submodules cleaned$(DEF_COLOR)"

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

# Installs/Updates homebrew (called manually cause slow af)
brew:
	$(HIDE) bash include/brew_install.sh
	@echo "$(BLUE)Brew set up$(DEF_COLOR)"
	@echo "$(RED)CLOSE AND REOPEN TERMINAL IF IT DOESN'T WORK$(DEF_COLOR)"

# Installs/Updates cmake (called manually cause slow af)
cmake:
	$(HIDE) brew install cmake
	@echo "$(BLUE)Cmake set up$(DEF_COLOR)"

# Installs/Updates cmake (called manually cause slow af)
glfw:
	$(HIDE) brew install glfw
	@echo "$(BLUE)GLFW set up$(DEF_COLOR)"
