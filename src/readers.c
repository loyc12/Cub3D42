/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/06/06 10:58:03 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//copies the .cub file's contents into d.level
void	read_file(int fd)
{
	char		*c;
	t_master	*d;
	int			i;

	c = ft_calloc(1, sizeof(char *));
	d = get_master();
	d->level = ft_calloc(M_CHARS, sizeof(char *));

	i = -1;
	while (++i < M_CHARS)
	{
		if (0 < read(fd, c, 1))
			d->level[i] = c[0];
		else
			break ;
	}
	ft_free_null(ADRS c);
	close(fd);
	if (M_CHARS <= i)
		close_with_error(ERR_MAP_SIZE);
}

//Verifies that the texture paths are valid
void	check_assets(void)
{
	t_master	*d;
	int			fd;
	int			i;

	d = get_master();
	i = 3;
	while (i >= 0) // checks asset paths [1] to [4]
	{
		if (d->t_paths[i])
		{
			fd = open(d->t_paths[i], O_RDONLY);
			if (fd < 0)
				close_with_error(ERR_FILE_ASSET);
			close(fd);
		}
		else
			close_with_error(ERR_FILE_SPECS);
		i--;
	}
}

//Verifies that the floor & ceiling colours are within bounds
void	check_colours(void)
{
	t_master	*d;

	d = get_master();
	if (!(d->c_ceiling) || !(d->c_floor))
		close_with_error(ERR_FILE_SPECS);
	if (d->c_ceiling->r > 255 || d->c_ceiling->g > 255 || d->c_ceiling->b > 255 || \
		d->c_floor->r > 255 || d->c_floor->g > 255 || d->c_floor->b > 255)
		close_with_error(ERR_FILE_COLOR);
	if (d->c_ceiling->r < 0 || d->c_ceiling->g < 0 || d->c_ceiling->b < 0 || \
		d->c_floor->r < 0 || d->c_floor->g < 0 || d->c_floor->b < 0)
		close_with_error(ERR_FILE_COLOR);

}

//opens the .cub file and copies its contents into d.level
void	read_level(char *path)
{
	int	fd;
	int	i;

	i = 0;
	while (path[i])
		i++;

	fd = open(path, O_RDONLY);
	if (ft_strncmp(&path[i - 4], ".cub", 5))
		close_with_error(ERR_FILE_CUBE);
	if (fd <= 0)
		close_with_error(ERR_FILE_LEVEL);
	read_file(fd);
	close(fd);

	printf(">%s<\n\n", get_master()->level); //	0============ DEBUG ============0

	get_info();
	check_assets();
	check_colours();

}
