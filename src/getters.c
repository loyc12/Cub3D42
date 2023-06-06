/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:45:01 by llord             #+#    #+#             */
/*   Updated: 2023/06/06 11:44:38 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//gets a colour component from a line
int	get_next_num(char *line, int *i)				//TODO : discriminate symbols (only digits, ',' and ' ')
{
	int	num;
	int	j;

	j = 0;
	num = 0;
	while (line[*i] && line[*i] != '\n' && !ft_isdigit(line[*i]))
		(*i)++;
	while (line[*i] && line[*i] != '\n' && ft_isdigit(line[*i]))
	{
		num *= 10;
		num += line[*i] - '0';
		(*i)++;
		j++;
	}
	if (j == 0)
		num = -1;
	return (num);
}

//extracts and returns the colour found in a given line
void	get_colour(char *line, t_colour **c)
{
	int			i;

	if (*c) //		frees and voids previous colour
		ft_free_null((void **)*c);

	*c = ft_calloc(1, sizeof(t_colour));
	i = 2; // skips initial info

	(*c)->r = get_next_num(line, &i);
	(*c)->g = get_next_num(line, &i);
	(*c)->b = get_next_num(line, &i);

	while (line[i] && line[i] != '\n')
	{
		if (!ft_isspace(line[i]))
			(*c)->b = -1; //		renders colour invalid if more than 3 nums on line
		i++;
	}

	i = 0;
	while (line[i] && line[i] != '\n')
		line[i++] = '\n'; //	voids everything
}

//extracts and returns the path found in a given line
void	get_texture(char *line, char **path)
{
	int		i;
	int		j;

	if (*path) //		frees and voids previous path
		ft_free_null((void **)path);

	i = 3; //					skips initial info
	while (line[i] && ft_isspace(line[i]))
		i++; //					skips initial spaces
	j = 0;
	while (line[i + j] && !ft_isspace(line[i + j]) && line[i + j] != '\n')
		j++; //					finds the lenght of the path string
	if (j > 0)
	{
		*path = ft_calloc(j + 1, sizeof(char));
		ft_strlcpy(*path, &(line[i]), j + 1);
	}
	i = 0;
	while (line[i] && line[i] != '\n')
		line[i++] = '\n'; //	voids everything
}

//parses the non-map info from d.level and voids it (replaces it by \n)
void	get_info(void)
{
	t_master	*d;
	int			i;

	d = get_master();
	d->t_paths = ft_calloc(A_COUNT + 1, sizeof(char *));
	i = -1;

	while (d->level[++i])
	{
		if (!ft_strncmp(&(d->level[i]), "NO ", 3))
			get_texture(&(d->level[i]), &(d->t_paths[TID_1_NORTH]));
		else if (!ft_strncmp(&(d->level[i]), "EA ", 3))
			get_texture(&(d->level[i]), &(d->t_paths[TID_1_EAST]));
		else if (!ft_strncmp(&(d->level[i]), "SO ", 3))
			get_texture(&(d->level[i]), &(d->t_paths[TID_1_SOUTH]));
		else if (!ft_strncmp(&(d->level[i]), "WE ", 3))
			get_texture(&(d->level[i]), &(d->t_paths[TID_1_WEST]));
		else if (!ft_strncmp(&(d->level[i]), "C ", 2))
			get_colour(&(d->level[i]), &(d->c_ceiling));
		else if (!ft_strncmp(&(d->level[i]), "F ", 2))
			get_colour(&(d->level[i]), &(d->c_floor));

		if (is_map_start(i))
			break ;
		else
			d->level[i] = '\n';
	}
}
