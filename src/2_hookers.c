/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_hookers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:46:03 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 13:13:50 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	apply_movements(t_master *data)
{
	if (data->move_front)
		move_towards(0);
	if (data->move_right)
		move_towards(90);
	if (data->move_back)
		move_towards(180);
	if (data->move_left)
		move_towards(270);
	if (data->turn_right)
		turn_right();
	if (data->turn_left)
		turn_left();
}

//normal hook used during the game loop
void	loop_hook(void *param)
{
	t_master	*data;
	double		f;
	int			i;

	data = (t_master *)param;
	apply_movements(data);
	i = -data->half_width;
	if (data->should_refresh)
	{
		while (i < data->half_width)
		{
			f = data->fov_ratio * i;
			f *= sin((180 - f) * M_PI / 360);
			draw_slice(data, cast_ray(data->player->vector, f), i);
			i++;
		}
		data->should_refresh = false;
	}
}

//key hook used during the game loop
void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_master	*d;

	d = (t_master *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		key_esc();
	if (!(keydata.key == MLX_KEY_ESCAPE && !d->should_refresh))
	{
		if (keydata.key == MLX_KEY_W && keydata.action != MLX_REPEAT)
			d->move_front = !d->move_front;
		if (keydata.key == MLX_KEY_E && keydata.action != MLX_REPEAT)
			d->move_right = !d->move_right;
		if (keydata.key == MLX_KEY_S && keydata.action != MLX_REPEAT)
			d->move_back = !d->move_back;
		if (keydata.key == MLX_KEY_Q && keydata.action != MLX_REPEAT)
			d->move_left = !d->move_left;
		if (keydata.key == MLX_KEY_D && keydata.action != MLX_REPEAT)
			d->turn_right = !d->turn_right;
		if (keydata.key == MLX_KEY_A && keydata.action != MLX_REPEAT)
			d->turn_left = !d->turn_left;
		if (keydata.key == MLX_KEY_LEFT_SHIFT && keydata.action != MLX_REPEAT)
			d->run = !d->run;
	}
}
