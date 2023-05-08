#------------------------------------------------------------------------------#
#                              PROJECT VARIABLES                               #
#------------------------------------------------------------------------------#

# Executable name
NAME	=	cub3D

# Arguments to call the executable with by default
ARGS	=	./maps/test_map_1.cub

# Directory names
SRCDIR		=	src/
OBJDIR		=	bin/
TSTDIR		=	tests/
SUBDIRS		=	\

# Source file names (prefix their subdir if needed)
FILES	=	main \
			tilers \
			getters \
			readers \
			freeers \
			flooders \
			coorders \
			initializers \

# Libraries (.a files) to include for compilation
LIBS	=	./Libft42/libft.a \
			./MLX42/build/libmlx42.a \

LIBX	=	-lglfw -L "/Users/$$USER/.brew/opt/glfw/lib/"
