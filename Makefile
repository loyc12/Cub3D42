include Settings.mk

#------------------------------------------------------------------------------#
#                                   COLOURS                                    #
#------------------------------------------------------------------------------#

# Dark colours (Becomes light if bold)
DMAGENTA	=\033[0;35m
DRED		=\033[0;31m
DYELLOW		=\033[0;33m
DGREEN		=\033[0;32m
DCYAN		=\033[0;36m
DBLUE		=\033[0;34m

# Light colours
MAGENTA		=\033[1;95m
RED			=\033[1;91m
YELLOW		=\033[1;93m
GREEN		=\033[1;92m
CYAN		=\033[1;96m
BLUE		=\033[1;94m

# Grayscale colours
DEFCOL		=\033[0m
BLACK		=\033[1;30m
GRAY		=\033[1;90m
LGRAY		=\033[1;37m
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
.PHONY: all
		long quick \
		ldirs deps \
		clean clear \
		fclean fclear \
		xclean xclear \
		re run rerun \
		leaks releaks \
		vleaks revleaks \
		norm libft \
		brew cmake \
		glfw grind \

#------------------------------------------------------------------------------#
#                                    FLAGS                                     #
#------------------------------------------------------------------------------#

# Flags for gcc, valgrind and leaks
CFLAGS	=	-Wall -Werror -Wextra $(XFLAGS)
LFLAGS	=	-atExit
VFLAGS	=	--leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes

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

# Shortcuts
CC		=	gcc
RM		=	rm -rf
CPY		=	cp -f
MKDR	=	mkdir -p
INCLUDE =	-I include

# Creates file paths
SRCS	=	$(addprefix $(SRCDIR), $(addsuffix .c, $(FILES)))
OBJS	=	$(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))


#------------------------------------------------------------------------------#
#                                 BASE TARGETS                                 #
#------------------------------------------------------------------------------#

# For full install (except brew)
long: mkdirs cmake glfw deps $(NAME)

# For standard compilation
all: mkdirs deps $(NAME)

# To skip submodule compilation
quick: mkdirs $(NAME)

# Creates object directory
mkdirs:
	$(HIDE) $(MKDR) $(OBJDIR)

# Compiles all files into an executable
$(NAME): $(OBJS)
	@echo "$(GREEN)Files compiled with flags : $(CFLAGS)$(DEFCOL)"
	@echo "$(DEFCOL)"
	$(HIDE) $(CC) $(MODE) $(CFLAGS) -o $@ $^ $(INCLUDE) $(LIBS) $(LIBX)
	@echo "$(CYAN)Executable created! $(DEFCOL)"
	@echo "$(DEFCOL)"

# Compiles each source file into a .o file
$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
	@echo "$(YELLOW)Compiling file : $< $(DEFCOL)"
	$(HIDE) $(CC) $(MODE) $(CFLAGS) -c $< -o $@ $(INCLUDE)

# Install dependencies via homebrew
deps:
	$(HIDE) git submodule init --quiet
	$(HIDE) git submodule update --quiet
	@echo "$(YELLOW)Initializing Libft42 module $(WHITE)"
	$(HIDE) cd Libft42 && make
	@echo "$(DEFCOL)"
	@echo "$(YELLOW)Initializing MLX42 module $(WHITE)"
	$(HIDE) cd MLX42 && cmake -B build && cmake --build build -j4
	@echo "$(DEFCOL)"
	@echo "$(GREEN)Submodules initiated $(DEFCOL)"
	@echo "$(DEFCOL)"

#------------------------------------------------------------------------------#
#                               CLEANING TARGETS                               #
#------------------------------------------------------------------------------#

# Removes objects
clear: clean
clean:
	$(HIDE) $(RM) $(OBJS)
	$(HIDE) $(RM) $(NAME).dSYM
	@echo "$(MAGENTA)Deleted object files $(DEFCOL)"
	$(HIDE) cd Libft42 && make clean
	@echo "$(MAGENTA)Deleted Libft object files $(DEFCOL)"
	@echo "$(DEFCOL)"

# Removes object dir and executable
fclear: fclean
fclean: clean
	$(HIDE) $(RM) $(OBJDIR)
	@echo "$(RED)Deleted object directory $(DEFCOL)"
	$(HIDE) $(RM) $(NAME)
	@echo "$(RED)Deleted executable $(DEFCOL)"
	$(HIDE) cd Libft42 && make fclean
	@echo "$(DEFCOL)"

xclear: xclean
xclean: fclean
	$(HIDE) git submodule deinit --quiet --all -f
	@echo "$(RED)Submodules emptied $(DEFCOL)"
	@echo "$(DEFCOL)"

# Removes object dir and executable and remakes everything
re: fclean all
	@echo "$(CYAN)Rebuilt everything! $(DEFCOL)"
	@echo "$(DEFCOL)"

#------------------------------------------------------------------------------#
#                               SHORTCUT TARGETS                               #
#------------------------------------------------------------------------------#

# Runs the program
rerun: re run
run: quick
	@echo "$(YELLOW)Launching command : ./$(NAME) $(ARGS) $(DEFCOL)"
	@echo "$(RED)"
	$(HIDE) ./$(NAME) $(ARGS) || true
	@echo "$(DEFCOL)"
	@echo "$(GREEN)Exited normally! $(DEFCOL)"
	@echo "$(DEFCOL)"

# Runs the program with leaks
releaks: re leaks
leaks: all
	@echo "$(YELLOW)Launching command : leaks $(LFLAGS) -- ./$(NAME) $(ARGS) $(DEFCOL)"
	@echo "$(RED)"
	$(HIDE) leaks $(LFLAGS) -- ./$(NAME) $(ARGS) || true
	@echo "$(DEFCOL)"
	@echo "$(GREEN)Exited normally! $(DEFCOL)"
	@echo "$(DEFCOL)"

# Runs the program with valgrind
revleaks: re vleaks
vleaks: all
	@echo "$(YELLOW)Launching command : valgrind $(VFLAGS) ./$(NAME) $(ARGS) $(DEFCOL)"
	@echo "$(RED)"
	$(HIDE) valgrind $(VFLAGS) --suppressions=include/supp ./$(NAME) $(ARGS) || true
	@echo "$(DEFCOL)"
	@echo "$(GREEN)Exited normally! $(DEFCOL)"
	@echo "$(DEFCOL)"

# Runs the norminette
norm:
	@echo "$(DEFCOL)"
	@echo "$(YELLOW)Norminetting .c files $(RED)"
	@norminette $(SRCS) | grep Error || true
	@echo "$(DEFCOL)"
	@echo "$(YELLOW)Norminetting .h files $(RED)"
	@norminette include | grep Error || true
	@echo "$(DEFCOL)"

# Updates the libft module (requires push after)
libft:
	@echo "$(YELLOW)Updating libft to latest commit $(WHITE)"
	$(HIDE) cd Libft42 && git pull origin main
	@echo "$(GREEN)Libft updated! $(DEFCOL)"
	@echo "$(DEFCOL)"

#------------------------------------------------------------------------------#
#                                 BREW TARGETS                                 #
#------------------------------------------------------------------------------#

# Installs/Updates homebrew (called manually cause slow af)
brew:
	$(HIDE) bash include/brew_install.sh
	@echo "$(BLUE)Brew installed $(DEFCOL)"
	@echo "$(RED)CLOSE AND REOPEN TERMINAL IF IT DOESN'T WORK$(DEFCOL)"
	@echo "$(GREEN)Exited normally! $(DEFCOL)"
	@echo "$(DEFCOL)"

# Installs/Updates cmake
cmake:
	@echo "$(YELLOW)Installing Cmake $(DEFCOL)"
	$(HIDE) brew install cmake
	@echo "$(BLUE)Cmake installed $(DEFCOL)"
	@echo "$(DEFCOL)"

# Installs/Updates cmake
glfw:
	@echo "$(YELLOW)Installing GFLW $(DEFCOL)"
	$(HIDE) brew install glfw
	@echo "$(BLUE)GLFW installed $(DEFCOL)"
	@echo "$(DEFCOL)"

# Installs/Updates valgrind
grind:
	@echo "$(YELLOW)Installing Valgrind $(DEFCOL)"
	$(HIDE) brew tap LouisBrunner/valgrind
	$(HIDE) brew install --HEAD LouisBrunner/valgrind/valgrind
	@echo "$(BLUE)Valgrind installed $(DEFCOL)"
	@echo "$(DEFCOL)"