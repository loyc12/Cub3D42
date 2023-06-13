/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/06/13 14:33:08 by llord            ###   ########.fr       */
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

//	player->vector->d = 186; //	0======== DEBUG ========0

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

void	key_esc(void)
{
	printf("ESC touched\n");
	mlx_close_window(get_master()->window);
	return ;
}

void	mv_front(void)
{
	printf("W touched\n");
	return ;
}

void	mv_back(void)
{
	printf("S touched\n");
	return ;
}

void	turn_left(void)
{
	printf("D touched\n");
	return ;
}

void	turn_right(void)
{
	printf("A touched\n");
	return ;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	(void)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		key_esc();
	if (!(keydata.key == MLX_KEY_ESCAPE))
	{
		if (keydata.key == MLX_KEY_W)
			mv_front();
		if (keydata.key == MLX_KEY_S)
			mv_back();
		if (keydata.key == MLX_KEY_D)
			turn_left();
		if (keydata.key == MLX_KEY_A)
			turn_right();
	}
}

void	init_window(void)
{
	t_master	*data;
	int			i;

	data = get_master();

	data->half_height = (SCREEN_HEIGHT / (PIXEL_SIZE * 2));
	data->half_width = (SCREEN_WIDTH / (PIXEL_SIZE * 2));
	data->window = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "CUBE3D", false);

	make_canvas();

	i = -data->half_width;
	while (i < data->half_width)
	{
		draw_slice(cast_ray(data->player->vector, i++)); //	0======== DEBUG ========0
	}


	mlx_key_hook(data->window, &key_hook, NULL);
	mlx_loop(data->window);
	mlx_terminate(data->window);
}

//creates the map grid from the map-info contained in d.level
void	init_map(void)
{
	check_map(); //				verifies each map character and the total map lenght
	build_map(get_master()); //	creates the unconnected tiles for the map grid
	connect_map(); //			connects all the map's tiles into a tile grid
	flood_check_map(); //		verifies that the map is closed around the player
}

//verifies the inputs (arguments and level file) are valid
void	init_game(int ac, char **av)
{
	if (ac != 2)
		close_with_error(ERR_ARG_COUNT);

	read_level(av[1]);

	printf(">%s<\n\n", get_master()->level); //	0============ DEBUG ============0

	init_map();
	init_player();

	init_window();

//	print_tiles(); //							0============ DEBUG ============0
//	print_paths(); //							0============ DEBUG ============0
//	print_colours(); //							0============ DEBUG ============0
//	print_player(); //							0============ DEBUG ============0

}
