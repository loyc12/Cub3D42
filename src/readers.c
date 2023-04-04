/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/04/04 12:40:32 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//reads the .cub file and stores it in d.level
void	read_level(int fd)
{
	char	*c;
	t_data	*d;
	int		i;

	c = ft_calloc(1, sizeof(char *));
	d = get_data();
	d->lvl = ft_calloc(M_CHARS, sizeof(char *));

	i = -1;
	while (++i < M_CHARS)
	{
		if (0 < read(fd, c, 1))
			d->lvl[i] = c[0];
		else
			break ;
	}
	ft_free_null(ADRS c);
	if (M_CHARS <= i)
	{
		ft_puterr(ERR_LVL_SI);
		d->state = MSTATE_ERROR;
	}
}
