/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:46:03 by llord             #+#    #+#             */
/*   Updated: 2023/06/14 14:20:10 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_esc(void)
{
	printf("ESC touched\n");
	mlx_close_window(get_master()->window);
	return ;
}

void	move_towards(double angle)
{
	t_entity	*player;

	player = get_master()->player;
	move_entity(player, angle);

	printf("New player position = %.3f : %.3f\n", player->vector->x, player->vector->y);
	get_master()->should_refresh = true;
}

void	turn_left(void)
{
	t_vector	*pv;

	pv = get_master()->player->vector;

	pv->d = normalize_angle(pv->d + TURN_SPEED);

	printf("New player angle : %.3f\n", pv->d); //	0======== DEBUG ========0
	get_master()->should_refresh = true;
}

void	turn_right(void)
{
	t_vector	*pv;

	pv = get_master()->player->vector;
	pv->d = normalize_angle(pv->d - TURN_SPEED);

	printf("New player angle : %.3f\n", pv->d); //	0======== DEBUG ========0
	get_master()->should_refresh = true;
}
