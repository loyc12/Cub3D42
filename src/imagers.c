/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imagers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/13 14:51:11 by llord            ###   ########.fr       */
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
			//printf("%i (%i) : %i (%i) | %i\n", x, x + dx, y, y + dy, c); //		0======== DEBUG ========0
			mlx_put_pixel(get_master()->canvas, (uint32_t)(x + dx), (uint32_t)(y + dy), (uint32_t)c);
			dx++;
		}
		dy++;
	}
}

//draws a macro pixel vertical line on the screen (0 is at the right of the center)
void	draw_slice(t_slice *slice, int screen_pos)
{
	t_master	*d;
	uint32_t	wall_colour;
	int			y;

	d = get_master();
	wall_colour = (0 << 24 | 192 << 16 | 0 << 8 | 255); //		0======== DEBUG ========0

	y = -d->half_height;
	while (y < d->half_height)
	{
		if ((slice->size * -d->half_height) <= y && y < (slice->size * d->half_height))
			draw_square(screen_pos, y, wall_colour); //	0======== DEBUG ========0
		y++;
	}
	ft_free_null(ADRS slice);
}

//initializes the background (canvas) to draw on
void	make_canvas(void)
{
	t_master	*d;
	int			canvas_colour[4];

	canvas_colour[0] = 0;
	canvas_colour[1] = 0;
	canvas_colour[2] = 0;
	canvas_colour[3] = 255;

	d = get_master();
	d->canvas = mlx_new_image(d->window, SCREEN_WIDTH, SCREEN_HEIGHT);

	ft_memfset(d->canvas->pixels, canvas_colour, SCREEN_WIDTH * d->canvas->height * BPP, 4); //	0======== DEBUG ========0

	mlx_image_to_window(d->window, d->canvas, 0, 0);

}

//initializes a single mlx image
mlx_texture_t	*make_texture(char *path)
{
	mlx_texture_t	*texture;
	xpm_t			*xpm;

	texture = ft_calloc(1, sizeof(texture));
	xpm = mlx_load_xpm42(path);

	*texture = xpm->texture; //		copies the texture from xpm_t
	mlx_delete_xpm42(xpm);

	return (texture);
}
