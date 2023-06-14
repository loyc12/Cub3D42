/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/06/14 11:01:31 by llord            ###   ########.fr       */
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
	d->level = ft_calloc(MAX_CHAR_COUNT, sizeof(char *));

	i = -1;
	while (++i < MAX_CHAR_COUNT)
	{
		if (0 < read(fd, c, 1))
			d->level[i] = c[0];
		else
			break ;
	}
	ft_free_null(ADRS c);
	close(fd);
	if (MAX_CHAR_COUNT <= i)
		close_with_error(ERR_MAP_SIZE);
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
