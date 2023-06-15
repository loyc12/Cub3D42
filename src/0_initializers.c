/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_initializers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 09:41:13 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player(void)
{
	t_master	*data;
	t_entity	*player;

	data = get_master();
	player = ft_calloc(1, sizeof(t_entity));
	player->vector = coords_to_vector(data->spawn->coords);
	player->radius = PLAYER_RADIUS;
	if (data->player_dir == 'E')
		player->vector->d = 0;
	if (data->player_dir == 'S')
		player->vector->d = 90;
	if (data->player_dir == 'W')
		player->vector->d = 180;
	if (data->player_dir == 'N')
		player->vector->d = 270;
	data->player = player;
}

//data->fov_ratio /= sin((180 - (PLAYER_FOV / 2)) * M_PI / 360);
//	compensates for fish eye effect compensation (lol)
void	init_window(void)
{
	t_master	*data;

	data = get_master();
	data->half_height = (SCREEN_HEIGHT / (PIXEL_SIZE * 2));
	data->half_width = (SCREEN_WIDTH / (PIXEL_SIZE * 2));
	data->window = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "CUBE3D", false);
	data->fov_ratio = ((PIXEL_SIZE * PLAYER_FOV) / SCREEN_WIDTH);
	data->fov_ratio /= sin((180 - (PLAYER_FOV / 2)) * M_PI / 360);
	data->should_refresh = true;
	make_canvas();
}

//creates the map grid from the map-info contained in d.level
void	init_map(void)
{
	check_map();
	build_map(get_master());
	connect_map();
	flood_check_map();
}

//verifies the inputs (arguments and level file) are valid
void	init_game(int ac, char **av)
{
	if (ac != 2)
		close_with_error(ERR_ARG_COUNT);
	read_level(av[1]);
	init_map();
	init_player();
	init_window();
}

//0============ DEBUG ============0
//	printf(">%s<\n\n", get_master()->level);
//	print_tiles();
//	print_paths();
//	print_colours();
//	print_player();
