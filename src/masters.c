/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 15:02:22 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//creates the t_master *d struct (first call behaviour)
t_master	*get_master(void)
{
	static t_master	*data;

	if (!data)
		data = ft_calloc(1, sizeof(t_master));
	return (data);
}

void	play_game(t_master *data)
{
	mlx_key_hook(data->window, &key_hook, data);
	mlx_loop_hook(data->window, &loop_hook, data);
	mlx_loop(data->window);
	mlx_terminate(data->window);
}

int	main(int ac, char **av)
{
	init_game(ac, av);
	play_game(get_master());
	printf("\n");
	return (free_master());
}
