/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/03/30 10:24:15 by llord            ###   ########.fr       */
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

// ======== DEFINITIONS ======== //

# define ERR_INIT	"Process Error : Initialization failure" //			internal error
# define ERR_ACTION	"Process Error : Invalid value given" //			internal error
# define ERR_ARG_CO	"Input Error : Invalid argument count"
# define ERR_ARG_TY	"Input Error : Specified file is not a .cub"
# define ERR_LVL_OP	"Level Error : File cannot be opened" //			inexistant or invalid perms
# define ERR_LVL_SP	"Level Error : File is missing specifications" //	such as wall textures or ceiling/floor colours
# define ERR_MAP_PL	"Map Error : Invalid number of player starting positions"
# define ERR_MAP_SY	"Map Error : Map uses invalid symbols"
# define ERR_MAP_SI	"Map Error : Map is too large"
# define ERR_MAP_OP	"Map Error : Map is not enclosed"

# define ADRS	(void **)&
# define ADRS2	(void ***)&

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
	TID_DEBUG	= 0,
	TID_NORTH	= 1,
	TID_EAST	= 2,
	TID_SOUTH	= 3,
	TID_WEST	= 4,
	TID_DOOR	= 5
}			t_tid;

//entity type (how should we interact with this entity)
typedef enum e_etype
{
	ETYPE_DEBUG		= 0,
	ETYPE_PLAYER	= 1,
	ETYPE_ENEMY		= 2,
}			t_etype;

//tile type (how should we interact/display this tile)
typedef enum e_ttype
{
	TTYPE_ERROR	= -1,
	TTYPE_VOID	= 0,
	TTYPE_ROOM	= 1,
	TTYPE_WALL	= 2,
}			t_ttype;

// ======== CONSTANTS ======== //

//rotation (1 rad ~= 57.3 deg)
# define PI			(float)3.14159265359
# define T_SPEED	(float)2.0 //	turning speed (in rad/sec)

//translation (1 tile ~= 3m)
# define W_SPEED	(float)0.4 //	walking speed (in tile/sec)
# define E_SPEED	(float)0.7 //	enemy speed  (in tile/sec)			(?)
# define R_SPEED	(float)1.0 //	running speed (in tile/sec)

//size
# define M_SIZE		256 //	maximum map size (in tiles)
# define A_SIZE		64 //	asset size (in pixels)
# define P_SIZE		4 //	size of virtual pixels (in real pixels)		(?)

//other
# define NO_CLIP	0 //	whether or not to ignore colision checks

// ======== STRUCTS ======== //

typedef struct s_data	t_data;
typedef struct s_tile	t_tile;

//int coordinates for tiles and screen
typedef struct s_coords
{
	int		x; //	north-south
	int		y; //	east-west
//	int		z; //	height												(?)

}			t_coords;

//float coordinates for entities and such
typedef struct s_vector
{
	float	x; //	north-south position
	float	y; //	east-west position
	float	d; //	orientation

}			t_vector;

//colour for floor and ceiling
typedef struct s_colour
{
	int		r; //	red
	int		g; //	green
	int		b; //	blue
//	int		a; //	alpha												(?)

}			t_colour;

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
	t_coords	*tc; //		tile coordinates
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
	t_asset		*sprite; //	asset to display 							(?)
	float		radius; //	colision radius (in tile size)

	//dynamic
	t_vector	*pv; //		unit coordinates (where inside the tile)

}				t_entity;

//the main global var for the program. holds generic data
typedef struct s_data
{
	//init
	int			lvl_fd;

	//static
	mlx_t		*window; //		where we draw stuff
	t_tile		**tiles; //		the game board itself
	t_colour	c_ceiling; //	ceiling colour
	t_colour	c_cloor; //		floor colour

	//dynamic
	t_entity	*player; //		player entity

	//graphics
	t_asset		**assets; //	array with all the assets

	//meta
	int			state; //		what the sim doin

}				t_data;

// ======== FUNCTIONS ======== //

//from main

//does_overlap_tile(entity, tile) //		checks for collision with walls
//does_overlap_entity(entity, entity)		only if implementing enemies/objects(?)

//move_entity(entity, direction) //			blocks at wall
//normalize_coords(entity) //				updates tc and uc when uc is outside of tc

#endif // CUB3D_H

// ======== NOTES AND IDEAS ======== //
