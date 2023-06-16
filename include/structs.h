/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/06/16 10:38:22 by llord            ###   ########.fr       */
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
	int		x;
	int		y;
}			t_coords;

//float coordinates for entities and such
typedef struct s_vector
{
	double	x;
	double	y;
	double	d;
}			t_vector;

//base component of the map
typedef struct s_tile
{
	t_coords	*coords;
	int			type;
	t_tile		*north;
	t_tile		*east;
	t_tile		*south;
	t_tile		*west;
	int			fff;
}				t_tile;

//for mobile objects
typedef struct s_entity
{
	double		radius;
	t_vector	*vector;
}				t_entity;

//colour for floor and ceiling
typedef struct s_colour
{
	int		r;
	int		g;
	int		b;
}			t_colour;

//...
typedef struct s_ray
{
	t_vector	*player_pos;
	double		x_ray_dist;
	double		y_ray_dist;
	double		ray_dist;
	double		ray_to_x_ratio;
	double		ray_to_y_ratio;
	double		x_to_ray_ratio;
	double		y_to_ray_ratio;
	double		x_coord;
	double		y_coord;
	double		wall_pos;
	double		angle;
	t_tile		*hit_tile; // TODO : use tile info instead of struct's copies
	int			hit_type;
	int			hit_dir;
	bool		ignore_x;
	bool		ignore_y;
	bool		is_checking_x;
}				t_ray;

//size = ~ 1 / hit distance
typedef struct s_slice
{
	double			dist;
	double			size;
	t_tile			*hit_tile; // TODO : use tile info instead of struct's copies
	int				hit_type;
	int				hit_dir;
	mlx_texture_t	*texture;
	double			texture_pos;
}					t_slice;

//the main global var for the program. holds generic data about the game
typedef struct s_master
{
	char			*level;
	int				map_start;
	t_colour		*c_ceiling;
	t_colour		*c_floor;
	char			**t_paths;
	mlx_t			*window;
	mlx_image_t		*canvas;
	mlx_texture_t	**textures;
	int				half_height;
	int				half_width;
	double			fov_ratio;
	bool			move_front;
	bool			move_right;
	bool			move_back;
	bool			move_left;
	bool			turn_right;
	bool			turn_left;
	bool			run;
	t_tile			**tiles;
	t_tile			*spawn;
	t_entity		*player;
	char			player_dir;
	int				player_spawn_count;
	int				master_state;
	bool			should_refresh;

}					t_master;

#endif // STRUCTS_H
