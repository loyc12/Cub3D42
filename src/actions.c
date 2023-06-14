/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:46:03 by llord             #+#    #+#             */
/*   Updated: 2023/06/14 11:32:55 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	t_vector	*pv;

	pv = get_master()->player->vector;

	pv->d = normalize_angle(pv->d - TURN_SPEED);

	printf("New player angle : %.3f\n", pv->d); //	0======== DEBUG ========0
}

void	turn_right(void)
{
	t_vector	*pv;

	pv = get_master()->player->vector;
	pv->d = normalize_angle(pv->d + TURN_SPEED);

	printf("New player angle : %.3f\n", pv->d); //	0======== DEBUG ========0
}
