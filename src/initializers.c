/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/06/12 11:20:35 by llord            ###   ########.fr       */
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

	player->vector->d = 30; //	0======== DEBUG ========0
/*
	if (data->player_dir == 'E')
		player->vector->d = 0;
	if (data->player_dir == 'S')
		player->vector->d = 90;
	if (data->player_dir == 'W')
		player->vector->d = 180;
	if (data->player_dir == 'N')
		player->vector->d = 270;
*/

	data->player = player;

}

void	init_window(void)
{
	mlx_t 	*mlx;

	printf("\ncheck 1\n"); //			0============ DEBUG ============0
	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "CUBE3D", false);
	printf("check 2\n"); //				0============ DEBUG ============0
	mlx_loop(mlx);
	printf("check 3\n"); //				0============ DEBUG ============0
	mlx_terminate(mlx);
	printf("check 4\n"); //				0============ DEBUG ============0
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

//	print_tiles(); //							0============ DEBUG ============0

//	init_window();
	print_paths(); //							0============ DEBUG ============0
	print_colours(); //							0============ DEBUG ============0
	print_player(); //							0============ DEBUG ============0

}
