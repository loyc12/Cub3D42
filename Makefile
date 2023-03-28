#------------------------------------------------------------------------------#
#                                   COLOURS                                    #
#------------------------------------------------------------------------------#

DEF_COLOR	=\033[0;39m
NC			=\033[0;39m
MAGENTA		=\033[1;95m
LMAGENTA	=\033[1;95m
RED			=\033[1;91m
LRED		=\033[1;91m
YELLOW		=\033[1;93m
LYELLOW		=\033[1;93m
GREEN		=\033[1;92m
LGREEN		=\033[1;92m
CYAN		=\033[1;96m
LCYAN		=\033[1;96m
BLUE		=\033[1;94m
GRAY		=\033[1;90m
WHITE		=\033[1;97m

# RED		: Deletion done (major)
# MAGENTA	: Deletion done (minor)

# YELLOW	: Task started
# GREEN		: Task done

# CYAN		: Creation done
# BLUE		: Installation done

#------------------------------------------------------------------------------#
#                                   GENERICS                                   #
#------------------------------------------------------------------------------#

# Special variables
DEFAULT_GOAL: all
.DELETE_ON_ERROR: $(NAME)
.PHONY: all ldirs \
		deps bonus \
		clean clear \
		fclean fclear \
		xclean xclear \
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
CPY		=	cp -f
MKDR	=	mkdir -p
INCLUDE =	-I include

# Executable name
NAME	=	cub3D

# Directory names
SRCDIR	=	src/
OBJDIR	=	bin/
TSTDIR	=	tests/

SUBDIRS	=

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
#                                 BASE TARGETS                                 #
#------------------------------------------------------------------------------#


all: mkdirs deps $(NAME)

# Creates object directory
mkdirs:
	$(HIDE) $(MKDR) $(OBJDIR)

# Compiles all files into an executable
$(NAME): $(OBJS)
	@echo "$(GREEN)Files compiled with flags : $(CFLAGS)$(DEF_COLOR)"
	@echo "$(DEF_COLOR)"
	$(HIDE) $(CC) $(MODE) $(CFLAGS) -o $@ $^ $(INCLUDE) $(LIBS) $(LIBX)
	@echo "$(CYAN)Executable created! $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"

# Compiles each source file into a .o file
$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
	@echo "$(YELLOW)Compiling file : $< $(DEF_COLOR)"
	$(HIDE) $(CC) $(MODE) $(CFLAGS) -c $< -o $@ $(INCLUDE)

# Install dependencies via homebrew
deps: cmake glfw
	$(HIDE) git submodule init --quiet
	$(HIDE) git submodule update --quiet
	@echo "$(YELLOW)Initializing Libft42 module $(WHITE)"
	$(HIDE) cd Libft42 && make
	@echo "$(DEF_COLOR)"
	@echo "$(YELLOW)Initializing MLX42 module $(WHITE)"
	$(HIDE) cd MLX42 && cmake -B build && cmake --build build -j4
	@echo "$(DEF_COLOR)"
	@echo "$(GREEN)Submodules initiated $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"

#------------------------------------------------------------------------------#
#                               CLEANING TARGETS                               #
#------------------------------------------------------------------------------#

# Removes objects
clear: clean
clean:
	$(HIDE) $(RM) $(OBJS)
	$(HIDE) $(RM) $(NAME).dSYM
	@echo "$(MAGENTA)Object files cleaned $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"
	$(HIDE) cd Libft42 && make fclean
	@echo "$(DEF_COLOR)"

# Removes object dir and executable
fclear: fclean
fclean: clean
	$(HIDE) $(RM) $(OBJDIR)
	@echo "$(MAGENTA)Object directory cleaned $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"
	$(HIDE) $(RM) $(NAME)
	@echo "$(RED)Executable cleaned $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"

xclear: xclean
xclean: fclean
	$(HIDE) git submodule deinit --quiet --all -f
	@echo "$(RED)Submodules emptied $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"

# Removes object dir and executable and remakes everything
re: fclean all
	@echo "$(CYAN)Rebuilt everything! $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"

#------------------------------------------------------------------------------#
#                               SHORTCUT TARGETS                               #
#------------------------------------------------------------------------------#

# Runs the program
rerun: re run
run: all
	@echo "$(YELLOW)Launching command : $(CMD) $(DEF_COLOR)"
	@echo "$(WHITE)"
	$(HIDE) $(CMD)
	@echo "$(DEF_COLOR)"
	@echo "$(GREEN)Exited normally! $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"

# Runs the program with valgrind
releaks: re leaks
leaks: all
	@echo "$(YELLOW)Launching command with leaks check : $(CMD) $(DEF_COLOR)"
	@echo "$(WHITE)"
	$(HIDE) valgrind --show-leak-kinds=all --trace-children=yes --leak-check=full --track-fds=yes --suppressions=include/supp $(CMD)
	@echo "$(DEF_COLOR)"
	@echo "$(GREEN)Exited normally! $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"

# Runs the norminette
norm:
	@echo "$(DEF_COLOR)"
	@echo "$(YELLOW)Norminetting .c files $(RED)"
	@norminette $(SRCS) | grep Error:
	@echo "$(YELLOW)Norminetting .h files $(RED)"
	@norminette include | grep Error:
	@echo "$(DEF_COLOR)"

#------------------------------------------------------------------------------#
#                                 BREW TARGETS                                 #
#------------------------------------------------------------------------------#

# Installs/Updates homebrew (called manually cause slow af)
brew:
	$(HIDE) bash include/brew_install.sh
	@echo "$(BLUE)Brew installed $(DEF_COLOR)"
	@echo "$(RED)CLOSE AND REOPEN TERMINAL IF IT DOESN'T WORK$(DEF_COLOR)"
	@echo "$(GREEN)Exited normally! $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"

# Installs/Updates cmake
cmake:
	@echo "$(YELLOW)Installing Cmake $(DEF_COLOR)"
	$(HIDE) brew install cmake
	@echo "$(BLUE)Cmake Installed $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"

# Installs/Updates cmake
glfw:
	@echo "$(YELLOW)Installing GFLW $(DEF_COLOR)"
	$(HIDE) brew install glfw
	@echo "$(BLUE)GLFW Installed $(DEF_COLOR)"
	@echo "$(DEF_COLOR)"
