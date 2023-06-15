/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_slicers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 11:57:20 by llord            ###   ########.fr       */
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
	double		floor_shade;
	double		wall_shade;
	uint32_t	wall_colour[4];


	//0======== DEBUG ========0
	d = get_master();

	wall_shade = (S_FACTOR / (slice->dist + 1)) + (1 - S_FACTOR);
	//ARRAY 4TEXT DANS STRUCT;

	wall_colour[0] = ((int)(255 * wall_shade) << 24 | 0 << 16 | 0 << 8 | 255);
	wall_colour[1] = ((int)(255 * wall_shade) << 24 | (int)(255 * wall_shade) << 16 | 0 << 8 | 255);
	wall_colour[2] = (0 << 24 | (int)(255 * wall_shade) << 16 | 0 << 8 | 255);
	wall_colour[3] = (0 << 24 | 0 << 16 | (int)(255 * wall_shade) << 8 | 255);
	y = -(d->half_height);
	while (y < d->half_height)
	{
		floor_shade = fabs((double)y / (double)d->half_height * S_FACTOR) + (1 - S_FACTOR);

		if ((slice->size * -d->half_height) <= y && y < (slice->size
				* d->half_height))
			draw_square(screen_pos, y, wall_colour[slice->hit_dir]); //		implement get_colour(texture, x, y)
		else if (y < 0)
			draw_square(screen_pos, y, get_rgba(d->c_ceiling, ((2 - S_FACTOR) - floor_shade))); // makes the sky look better by inverting the shading
		else
			draw_square(screen_pos, y, get_rgba(d->c_floor, floor_shade));
		y++;
	}
	ft_free_null(ADRS slice);
}
//	printf("Scale : %.5f\n", scale); //	0======== DEBUG ========00

//converts a ray struct into a slice struct, used in drawing slices
t_slice	*create_slice(t_ray *r, double angle)
{
	t_slice	*slice;

	slice = ft_calloc(1, sizeof(t_slice));
	if (r->hit_type == TTYPE_ERROR)
	{
		slice->size = 0;
		return (ft_free_null(ADRS r), slice);
	}
	slice->dist = r->ray_dist * cos(M_PI * angle / 180);
	slice->size = set_precision(1 / slice->dist, 1073741824);
	slice->hit_type = r->hit_type;
	slice->hit_dir = r->hit_dir;
	//assign texture based on hit_dir
	slice->texture_pos = r->wall_pos;


	ft_free_null(ADRS r);
	return (slice);
}
//	printf("Texture pos : %.5f\n", slice->texture_pos); //	0======== DEBUG ========0
//	printf("Slice size : %.20f\n", slice->size); //	0======== DEBUG ========0

//initializes the background (canvas) to draw on
void	make_canvas(void)
{
	t_master	*d;
	int			canvas_colour[4]; //	0======== DEBUG ========0

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
