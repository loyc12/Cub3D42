/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/03/29 13:42:10 by llord            ###   ########.fr       */
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

//tile type (how should we interact/display this tile)
typedef enum e_ttype
{
	TTYPE_ERROR	= -1,
	TTYPE_VOID	= 0,
	TTYPE_ROOM1	= 1,
	TTYPE_WALL1	= 21,
	TTYPE_DOOR1	= 41
}			t_ttype;

// ======== CONSTANTS ======== //

//rotations
# define C_SCALE	1024 //	number of units in a circle's circumference
# define T_SPEED	3 //	turning speed (in C_SCALE units)

//translations
# define T_SIZE		128 //	tile size (in unit) (tiles ~ 3m x 3m x 3m)
# define W_SPEED	1 //	walking speed (in T_SIZE / T_RATE units)		1u/t ~= 0.75 m/s (with 128 and 32)
# define R_SPEED	3 //	running speed (in T_SIZE / T_RATE units)
# define E_SPEED	2 //	enemy speed  (in T_SIZE / T_RATE units)			(?)

//times
# define T_RATE		32 //	simulation speed (in T_RATE / sec)
# define A_RATE		4 //	animation speed (in frame / T_RATE units)		(?)
# define E_RATE		4 //	how often enemies re-think (every T_RATE units)	(?)

//other
# define M_SIZE		256 //	maximum map size (in tiles)
# define A_SIZE		64 //	asset size (in pixels)
# define P_SCALE	4 //	size of virtual pixels (in real pixels)			(?)

// ======== STRUCTS ======== //

typedef struct s_data	t_data;
typedef struct s_tile	t_tile;

//coordinates for general purposes (bc = (uc + (tc * T_SIZE )), sc = screen coords)
typedef struct s_coords
{
	int		x; //	north-south
	int		y; //	east-west
//	int		z; //	height													(?)
	int		d; //	direction (in)

}			t_coords;

//coordinates for general purposes (tile_pos, unit_pos, screen_pos)
typedef struct s_colour
{
	int		r; //	red
	int		g; //	green
	int		b; //	blue
	int		a; //	alpha									(?)

}			t_colour;

//data for a given asset
typedef struct s_asset
{
	//static
	int			id; //		tid / index in array

	//dynamic
	mlx_image_t	*image; //	current texture
//	mlx_image_t	*old;	//	next texture 									(?)
//	int			rf; //		replacement flag (for animations) 				(?)

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

	//meta
	int			state; //	if door is openned or smthg

}				t_tile;

//for mobile objects
typedef struct s_entity
{
	//static
	t_asset		*sprite; //	asset to display 								(?)
	int			radius; //	colision radius (in T_SIZE units)

	//dynamic
	t_coords	*uc; //		unit coordinates (where inside the tile)
	t_coords	*tc; //		tile coordinates

}				t_entity;

//the main global var for the program. holds generic data
typedef struct s_data
{
	//static
	mlx_t		*window; //		where we draw stuff
	t_tile		**tiles; //		the game board itself
	t_colour	c_ceiling; //	ceiling colour
	t_colour	c_cloor; //		floor colour
	int			tick_len; //	1000000 / T_RATE (in u_sec)

	//dynamic
	t_entity	*player; //		player entity

	//graphics
	t_asset		**assets; //	array with all the assets

	//cheats
	bool		noclip; //		walk through walls

	//meta
	int			state; //		what the sim doin

}				t_data;

// ======== FUNCTIONS ======== //

//from main

//get_lvl(file) //							extracts the level data (except the map)
//check_lvl()

//get_map(file) //							extracts the map data
//check_map()

//does_overlap_tile(entity, tile)
//does_overlap_entity(entity, entity)		(?)

//move_entity(entity, direction) //			blocks at wall
//normalize_coords(entity) //				updates tc and uc when uc is outside of tc

#endif