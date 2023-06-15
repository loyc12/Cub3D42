/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_slicers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 10:10:27 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//draws a macro pixel on the screen (0:0 is at the bottom right of the center)
void	draw_square(int x, int y, int c)
{
	int	dx;
	int	dy;

	x = (PIXEL_SIZE * x) + (SCREEN_WIDTH / 2);
	y = (PIXEL_SIZE * y) + (SCREEN_HEIGHT / 2);
	dy = 0;
	while (dy < PIXEL_SIZE)
	{
		dx = 0;
		while (dx < PIXEL_SIZE)
		{
			mlx_put_pixel(get_master()->canvas, (uint32_t)(x + dx), \
				(uint32_t)(y + dy), (uint32_t)c);
			dx++;
		}
		dy++;
	}
}
//printf("%i (%i) : %i (%i) | %i\n", x, x + dx, y, y + dy, c);
//		0======== DEBUG ========0

//draws a macro pixel vertical line on the scr (0 is at the right of the center)
void	draw_slice(t_slice *slice, int screen_pos)
{
	t_master	*d;
	int			y;
	uint32_t	wall_colour[4];

	//0======== DEBUG ========0
	d = get_master();
	wall_colour[0] = (128 << 24 | 0 << 16 | 0 << 8 | 255);
	wall_colour[1] = (0 << 24 | 128 << 16 | 0 << 8 | 255);
	wall_colour[2] = (0 << 24 | 0 << 16 | 128 << 8 | 255);
	wall_colour[3] = (192 << 24 | 192 << 16 | 1992 << 8 | 255);
	y = -d->half_height;
	while (y < d->half_height)
	{
		if ((slice->size * -d->half_height) <= y && y < (slice->size
				* d->half_height))
			draw_square(screen_pos, y, wall_colour[slice->hit_dir]);
		//	0======== DEBUG ========0
		else if (y < 0)
			draw_square(screen_pos, y, get_rgba(d->c_ceiling));
		//		0======== DEBUG ========0
		else
			draw_square(screen_pos, y, get_rgba(d->c_floor));
		//		0======== DEBUG ========0
		y++;
	}
	ft_free_null(ADRS slice);
}

//converts a ray struct into a slice struct, used in drawing slices
//	compensates for fish eye effect
//	avoids jiterry walls
t_slice	*create_slice(t_ray *r, double angle)
{
	t_slice	*slice;

	slice = ft_calloc(1, sizeof(t_slice));
	if (r->hit_type == TTYPE_ERROR)
	{
		slice->size = 0;
		return (ft_free_null(ADRS r), slice);
	}
	r->ray_dist *= cos(M_PI * angle / 180);
	slice->size = set_precision(1 / r->ray_dist, 1073741824);
	slice->hit_type = r->hit_type;
	//also need to find texture_pos and get right texture
	slice->hit_dir = r->hit_dir;
	ft_free_null(ADRS r);
	return (slice);
}
//	printf("Slice size : %.20f\n", slice->size); //	0======== DEBUG ========0

//initializes the background (canvas) to draw on
void	make_canvas(void)
{
	t_master	*d;

	int canvas_colour[4];   //	0======== DEBUG ========0
	canvas_colour[0] = 0;   //	0======== DEBUG ========0
	canvas_colour[1] = 0;   //	0======== DEBUG ========0
	canvas_colour[2] = 0;   //	0======== DEBUG ========0
	canvas_colour[3] = 255; //	0======== DEBUG ========0
	d = get_master();
	d->canvas = mlx_new_image(d->window, SCREEN_WIDTH, SCREEN_HEIGHT);
	ft_memfset(d->canvas->pixels, canvas_colour, SCREEN_WIDTH
		* d->canvas->height * BPP, 4);
//	0======== DEBUG ========0
	mlx_image_to_window(d->window, d->canvas, 0, 0);
}
