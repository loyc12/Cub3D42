/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:46:03 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 09:54:50 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_esc(void)
{
	mlx_close_window(get_master()->window);
	return ;
}
//	printf("ESC touched\n");

void	move_towards(double angle)
{
	t_entity	*player;

	player = get_master()->player;
	move_entity(player, angle);
	get_master()->should_refresh = true;
}
//	printf("New player position = %.3f : %.3f\n", player->vector->x, player->vector->y);

void	turn_left(void)
{
	t_vector	*pv;

	pv = get_master()->player->vector;
	if (get_master()->run)
		pv->d = normalize_angle(pv->d + (TURN_SPEED * RUN_FACTOR));
	else
		pv->d = normalize_angle(pv->d + TURN_SPEED);
	get_master()->should_refresh = true;
}
//printf("New player angle : %.3f\n", pv->d); //	0======== DEBUG ========0

void	turn_right(void)
{
	t_vector	*pv;

	pv = get_master()->player->vector;
	if (get_master()->run)
		pv->d = normalize_angle(pv->d - (TURN_SPEED * RUN_FACTOR));
	else
		pv->d = normalize_angle(pv->d - TURN_SPEED);
	get_master()->should_refresh = true;
}
//	printf("New player angle : %.3f\n", pv->d); //	0======== DEBUG ========0