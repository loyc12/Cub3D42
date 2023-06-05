/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/06/05 13:42:38 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

//extracts and returns the path found in a given line
char	*get_texture(char *line)
{
	char	*path;
	int		i;
	int		j;

	path = NULL;
	i = 3; //					skips initial info
	while (line[i] && ft_isspace(line[i]))
		i++; //					skips initial spaces
	j = 0;
	while (line[i + j] && !ft_isspace(line[i + j]) && line[i + j] != '\n')
		j++; //					finds the lenght of the path string
	if (j > 0)
	{
		path = ft_calloc(j + 1, sizeof(char));
		ft_strlcpy(path, &(line[i]), j + 1);
	}
	i = 0;
	while (line[i] && line[i] != '\n')
		line[i++] = '\n'; //	voids everything
	return (path);
}

//gets a colour component from a line
int	get_next_num(char *line, int *i)
{
	int	num;

	num = 0;
	while (line[*i] && line[*i] != '\n' && !ft_isdigit(line[*i]))
		(*i)++;
	while (line[*i] && line[*i] != '\n' && ft_isdigit(line[*i]))
	{
		num *= 10;
		num += line[*i] - '0';
		(*i)++;
	}
	return (num);
}


//extracts and returns the colour found in a given line
t_colour	*get_colour(char *line)
{
	t_colour	*c;
	int			i;

	c = ft_calloc(1, sizeof(t_colour));
	i = 2; // skips initial info

	c->r = get_next_num(line, &i);
	c->g = get_next_num(line, &i);
	c->b = get_next_num(line, &i);

	i = 0;
	while (line[i] && line[i] != '\n')
		line[i++] = '\n'; //	voids everything
	return (c);
}


//parses the non-map info from d.level and voids it (replaces it by \n)
void	get_info(void)
{
	t_master	*d;
	int			i;

	d = get_master();
	d->t_paths = ft_calloc(A_COUNT, sizeof(char *));

	i = -1;
	while (d->level[++i]) //		THIS WILL LEAKS WHEN DUPLICATE TEXTURES/COLOURS
	{
		if (!ft_strncmp(&(d->level[i]), "NO ", 3))
			d->t_paths[TID_1_NORTH] = get_texture(&(d->level[i]));
		else if (!ft_strncmp(&(d->level[i]), "EA ", 3))
			d->t_paths[TID_1_EAST] = get_texture(&(d->level[i]));
		else if (!ft_strncmp(&(d->level[i]), "SO ", 3))
			d->t_paths[TID_1_SOUTH] = get_texture(&(d->level[i]));
		else if (!ft_strncmp(&(d->level[i]), "WE ", 3))
			d->t_paths[TID_1_WEST] = get_texture(&(d->level[i]));
		else if (!ft_strncmp(&(d->level[i]), "F ", 2))
			d->c_floor = get_colour(&(d->level[i]));
		else if (!ft_strncmp(&(d->level[i]), "C ", 2))
			d->c_ceiling = get_colour(&(d->level[i]));

		if (is_map_start(i))
			break ;
		else
			d->level[i] = '\n';
	}
}

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
	int			i;

	d = get_master();
	i = 4;
	while (i > 0)
	{
		if (d->t_paths[i])
		{
			img = open(d->t_paths[i], O_RDONLY);
			if (img < 0)
				close_with_error(ERR_FILE_OPEN);
			close(img);
		}
		else
			close_with_error(ERR_FILE_TEXT);
		i--;
	}
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
