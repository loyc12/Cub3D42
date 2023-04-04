/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/04/04 12:51:26 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//acts as a pseudo "global" t_data var
t_data	*get_data(void)
{
	static t_data	*d;

	if (!d)
	{
		d = ft_calloc(1, sizeof(t_data));
	}

	return (d);
}

//opens and copies the .cub file's content into d->lvl
void	get_lvl(char *path)
{
	int	fd;
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (ft_strncmp(&path[i - 4], ".cub", 5))
	{
		ft_puterr(ERR_ARG_TY);
		get_data()->state = MSTATE_ERROR;
	}
	fd = open(path, O_RDONLY);
	if (fd <= 0)
	{
		ft_puterr(ERR_FD_VAL);
		get_data()->state = MSTATE_ERROR;
	}
	read_level(fd); //	reads the .cub file and stores it in d.level
	close(fd);
}
