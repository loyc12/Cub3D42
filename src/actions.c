/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:46:03 by llord             #+#    #+#             */
/*   Updated: 2023/06/14 10:48:25 by llord            ###   ########.fr       */
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
	printf("D touched\n");
	get_master()->player->vector->d -= 1;
	//don't forget to normalize after
}

void	turn_right(void)
{
	printf("A touched\n");
	get_master()->player->vector->d += 1;
	//don't forget to normalize after
}