#------------------------------------------------------------------------------#
#                              PROJECT VARIABLES                               #
#------------------------------------------------------------------------------#

# Executable name
NAME	=	cub3D

# Arguments to call the executable with by default
ARGS	= ./levels/map_4.cub
#./levels/map_3.cub
# Directory names
SRCDIR		=	src/
OBJDIR		=	bin/
TSTDIR		=	tests/
SUBDIRS		=	\

# Source file names (prefix their subdir if needed)
FILES	=	2_actions \
			1_raycasters \
			0_checkers \
			0_coorders \
			debugers \
			4_freeers \
			3_getters \
			2_hookers \
			0_initializers \
			main \
			1_maths \
			2_movers \
			0_readers \
			3_slicers \
			3_textures \
			3_tilers \

# Libraries (.a files) to include for compilation
LIBS	=	./Libft42/libft.a \
			./MLX42/build/libmlx42.a \

LIBX	=	-lglfw -L "/Users/$$USER/.brew/opt/glfw/lib/"
