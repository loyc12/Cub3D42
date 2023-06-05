/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/06/05 11:35:09 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

//extracts and returns the path found in a given line
char	*get_texture(char *line)
{
	char	*path;
	int		i;
	int		j;
	int		k;

	path = NULL;
	i = 3; // skips initial info
	while (line[i] && ft_isspace(line[i]))
		i++;
	j = i;
	k = 0;
	while (line[j + k] && !ft_isspace(line[j + k]) && line[j + k] != '\n')
		k++;
	if (k > 0)
	{
		path = ft_calloc(j, sizeof(char));
		ft_strlcpy(path, &(line[j]), k + 1);
	}
	k += j;
	while (line[k] && line[k] != '\n')
		k++;
	i = 0;
	while (line[i] && i < k)
		line[i++] = '\n';
	return (path);
}

//extracts and returns the colour found in a given line
/*
t_colour	get_colour(char *line)
{
	int	i;

	i = 2; // skips initial info
}
*/

//parses the non-map info from d.level and voids it (replaces it by \n)
void	get_info(void)
{
	t_master	*d;
	int			i;

	d = get_master();
	d->t_paths = ft_calloc(A_COUNT, sizeof(char *));

	i = -1;
	while (d->level[++i]) //		THIS WILL LEAKS WHEN DUPLICATE TEXTURES
	{
		if (!ft_strncmp(&(d->level[i]), "NO ", 3))
			d->t_paths[TID_1_NORTH] = get_texture(&(d->level[i]));
		else if (!ft_strncmp(&(d->level[i]), "EA ", 3))
			d->t_paths[TID_1_EAST] = get_texture(&(d->level[i]));
		else if (!ft_strncmp(&(d->level[i]), "SO ", 3))
			d->t_paths[TID_1_SOUTH] = get_texture(&(d->level[i]));
		else if (!ft_strncmp(&(d->level[i]), "WE ", 3))
			d->t_paths[TID_1_WEST] = get_texture(&(d->level[i]));
//		else if (!ft_strncmp(&(d->level[i]), "F ", 2))
//			d->c_floor = get_colour(&(d->level[i]));
//		else if (!ft_strncmp(&(d->level[i]), "C ", 2))
//			d->c_ceiling = get_colour(&(d->level[i]));

		if (is_map_start(i))
			break ;
		else
			d->level[i] = '\n';
	}
}


/*
for each path in t_paths (1 to 4 )
	if t_paths[i]
		open(t_paths[i])
			check
		close(t_paths[i])

*/

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

/*
Check the path of assets and verify content is there and usable*/
void	check_asset(void)
{
	t_master	*d;
	int			img;
	int			r;
	int			i;

	d = get_master();
	i = 4;
	r = 0;
	while (i > 0)
	{
		if (d->t_paths[i])
		{
			img = open(d->t_paths[i], O_RDONLY);
			if (img < 0)
				r = 1;
			close(img);
		}
		else
		{
			r = 1;
			break ;
		}
		i--;
	}
	if (r == 1)
		close_with_error(ERR_FILE_OPEN);
}

//opens the .cub file and copies its contents into d.level
void	read_level(char *path)
{
	int	fd;
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (ft_strncmp(&path[i - 4], ".cub", 5))
		close_with_error(ERR_FILE_NAME);
	fd = open(path, O_RDONLY);
	if (fd <= 0)
		close_with_error(ERR_FILE_OPEN);
	read_file(fd);
	close(fd);
	printf(">%s<\n\n", get_master()->level); //	0============ DEBUG ============0

	get_info(); //		parses the non-map info from d.level and voids it (replaces it by \n)
	check_asset();

//	check_info(); //	verifies the texture paths and floor/ceiling colours

}
