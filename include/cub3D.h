/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/06/13 11:46:41 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ======== LIBRARIES ======== //

# include "../MLX42/include/MLX42/MLX42.h"
# include "../Libft42/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <math.h>

// ======== DEFINITIONS ======== // RENAME THEM TO MORE CONSCISE AND READABLE NAMES

# define ERR_INIT	"Process Error : Initialization failure" //				internal error
# define ERR_ACTION	"Process Error : Invalid value given" //				internal error

# define ERR_ARG_COUNT	"Input Error : Invalid argument count"

# define ERR_FILE_LEVEL	"File Error : Invalid level file path" //			inexistant file or invalid perms
# define ERR_FILE_CUBE	"File Error : Level file is not a .cub"
# define ERR_FILE_SIZE	"File Error : Level file is too large"
# define ERR_FILE_SPECS	"File Error : Level specification missing" //		wall assets paths or ceiling & floor colours
# define ERR_FILE_ASSET	"File Error : Invalid asset file path" //			inexistant file or invalid perms
# define ERR_FILE_COLOR	"File Error : Invalid colour code"

# define ERR_MAP_SIZE	"Map Error : Map is too large"
# define ERR_MAP_PLAYER	"Map Error : Map has an invalid number or players"
# define ERR_MAP_CHAR	"Map Error : Map uses invalid symbols"
# define ERR_MAP_BOUND	"MAP Error : Map is not enclosed"

# define ADRS	(void **)&
# define ADRS2	(void ***)&
# define BPP 	4 // sizeof(int32_t)

// ======== ENUM STATES ======== //

//machine states (where the program is at execution wise)
typedef enum e_mstate
{
	MSTATE_ERROR	= -1,
	MSTATE_STARTING	= 0,
	MSTATE_RUNNING	= 1,
	MSTATE_RESTART	= 2,
	MSTATE_ENDING	= 3

}			t_mstate;

//texture ID (the index of the texture in the asset array)
typedef enum e_tid
{
	TID_1_NORTH	= 0,
	TID_1_EAST	= 1,
	TID_1_SOUTH	= 2,
	TID_1_WEST	= 3
}			t_tid;

//entity type (how should we interact with this entity)
typedef enum e_etype
{
	ETYPE_DEBUG		= 0,
	ETYPE_PLAYER	= 1,
	ETYPE_ENEMY		= 2
}			t_etype;

//tile type (how should we interact/display this tile)
typedef enum e_ttype
{
	TTYPE_ERROR	= -1,
	TTYPE_ROOM	= 0,
	TTYPE_WALL	= 1
}			t_ttype;

// ======== CONSTANTS ======== //

//rotation (1 rad ~= 57.3 deg)
# define PI			(double)3.14159265359
//# define T_SPEED	(float)2.0 //	turning speed (in rad/sec)

//translation (1 tile ~= 3m)
# define WALK_SPEED		(double)0.4 //	walking speed (in tile/sec)
# define RUN_SPEED		(double)1.0 //	running speed (in tile/sec)

//sizes
# define MAX_CHAR_COUNT	(int)8192 //	maximum level file size (in chars)
# define MAX_MAP_SIZE	(int)64 //		maximum horizontal/vertical map size (in tiles)

# define ASSET_SIZE		(int)64 //		asset size (in pixels)
# define ASSET_COUNT	(int)4 //		asset count

# define SCREEN_WIDTH	(int)1536
# define SCREEN_HEIGHT	(int)1152
# define PIXEL_SIZE		(int)8 //		size of virtual pixels (in real pixels)

# define PLAYER_RADIUS	(double)0.1

//other
# define NO_CLIP	0 //			whether or not to ignore colision checks

// ======== STRUCTS ======== //

typedef struct s_data	t_data;
typedef struct s_tile	t_tile;

//int coordinates for tiles and screen
typedef struct s_coords
{
	int		x; //	north-south
	int		y; //	east-west
}			t_coords;

//float coordinates for entities and such
typedef struct s_vector
{
	double	x; //	east-west position
	double	y; //	north-south position
	double	d; //	degree

}			t_vector;

//data for a given asset
typedef struct s_asset
{
	//static
	int			id; //		tid / index in array

	//dynamic
	mlx_image_t	*image; //	current texture

}			t_asset;

//base component of the map
typedef struct s_tile
{
	//static
	t_coords	*coords; //	tile coordinates
	int			type; //	used for texturing and interactions

	//neighbours
	t_tile		*north;
	t_tile		*east;
	t_tile		*south;
	t_tile		*west;

	//dynamic
	int			fff; //		flood fill flag

}				t_tile;

//for mobile objects
typedef struct s_entity
{
	//static
//	t_asset		*sprite; //	asset to display 							(?)
	double		radius; //	colision radius (in tile size)

	//dynamic

	t_vector	*vector; //		unit coordinates (where inside the tile)

}				t_entity;

//colour for floor and ceiling // MAYBE ALREADY EXISTS IN MLX LIB
typedef struct s_colour
{
	int		r; //	red
	int		g; //	green
	int		b; //	blue
//	int		a; //	alpha												(?)

}			t_colour;

//colour for floor and ceiling // MAYBE ALREADY EXISTS IN MLX LIB
typedef struct s_ray
{
	t_vector	*player_pos;
	//distance traveled by the ray (when checking x|y hits)
	double		x_ray_dist;
	double		y_ray_dist;
	double		ray_dist; //	final distance found

	//multiplicative factors for x\y to/from ray conversion
	double		ray_to_x_ratio;
	double		ray_to_y_ratio;
	double		x_to_ray_ratio;
	double		y_to_ray_ratio;

	bool		ignore_x;
	bool		ignore_y;

	//x|y coords of the current hit check
	double		x_coord; //	final coord
	double		y_coord; //	final coord
	double		wall_pos; //final texture slice to use

	double		angle; //	final absolute angle
	int			hit_type; //final wall type

}				t_ray;

//the main global var for the program. holds generic data about the game and its state
typedef struct s_master
{
	//level infos (paths and colours)
	char		*level; //				where to store the raw .cub info
	int			map_start;
	t_colour	*c_ceiling; //			ceiling colour
	t_colour	*c_floor; //			floor colour
	char		**t_paths;

	//graphics
	mlx_t		*window; //				the mlx for the window
	mlx_image_t	*canvas;
//	t_asset		**assets; //			array with all the assets

	//environments
	t_tile		**tiles; //				the game board itself

	//entities
	t_tile		*spawn; //				pointer to spawn tile
	char		player_dir;
	t_entity	*player; //				player entity

	//meta
	int			player_spawn_count; //	player flag for map parsing
	int			master_state; //		what the sim doin

}				t_master;

// ======== FUNCTIONS ======== //

//from casters --- (5)
int				find_hit_type(t_ray *r);
void			find_first_ray_dists(t_ray *r);
bool			evaluate_x_hits(t_ray *r);
bool			evaluate_y_hits(t_ray *r);
t_ray			*cast_ray(t_vector *pos, double ray_angle);

//from checkers --- (5)
bool			is_char_valid(char c);
bool			is_map_start(int i);
void			check_map(void);
void			flood_check(t_tile *tile);
void			flood_check_map(void);

//from coorders
t_coords		*coords_copy(t_coords *_c);
t_vector		*coords_to_vector(t_coords	*_c);

//from debugers
void			print_tile(t_tile *tile);
void			print_tiles(void);
void			print_neighbours(t_tile *tile);
void			announce_tile(t_tile *tile, char c);
void			print_paths(void);
void			print_colours(void);
void			print_player(void);

//from freeers --- (4)
void			free_tiles(t_master *data);
void			free_entity(t_entity *entity);
int				free_master(void);
void			close_with_error(char *err);

//from getters --- (4)
int				get_next_num(char *line, int *i);
void			get_colour(char *line, t_colour **c);
void			get_texture(char *line, char **path);
void			get_info(void);

//from imager --- (2)
void			make_canvas(void);
mlx_texture_t	*make_texture(char *path);

//from initializers --- (4)
void			init_player(void);
void			init_window(void);
void			init_map(void);
void			init_game(int ac, char **av);

//from main
t_master		*get_master(void);

//maths.c
void			find_ratios(t_ray *r);

//from readers
void			read_file(int fd);
void			check_assets(void);
void			check_colours(void);
void			read_level(char *path);

//from tilers
t_tile			*create_tile(char c, t_coords *_coords);
t_tile			*find_tile(int x, int y);
void			build_map(t_master *data);
void			connect_map(void);

//does_overlap_tile(entity, tile) //		checks for collision with walls
//does_overlap_entity(entity, entity)		only if implementing enemies/objects(?)
//move_entity(entity, direction) //			blocks at wall

#endif // CUB3D_H

// ======== NOTES AND IDEAS ======== //
