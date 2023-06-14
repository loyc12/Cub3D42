/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/06/14 14:04:32 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
//	int			type;
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
	int			hit_dir;

}				t_ray;

//...
typedef struct s_slice
{
	double			size; //		~ 1 / hit distance
	int				hit_type; //	hit tile type
	int				hit_dir;
	mlx_texture_t	*texture; //	texture to use
	double			texture_pos; //	horizontal position in the texture

}					t_slice;

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
	int			half_height; //			half the height of the screen in PIXEL_SIZE
	int			half_width; //			half the width of the screen in PIXEL_SIZE

	double		fov_ratio;
	bool		should_refresh;
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

#endif // STRUCTS_H
