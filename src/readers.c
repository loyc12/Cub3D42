/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/05/26 15:57:39 by alvachon         ###   ########.fr       */
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
		exit_err(ERR_LVL_SI);
}

/*
Check the path of assets and verify content is there and usable*/
void	check_asset(void)
{
	int			env;
	int			h_container;
	int			l_container;
	int			m_container;
	int			r;

	r = 0;
	h_container = open("./assets/h_container.png", O_RDONLY);
		r = 1;
	l_container = open("./assets/l_container.png", O_RDONLY);
	if (l_container < 0)
		r = 1;
	m_container = open("./assets/m_container.png", O_RDONLY);
	if (m_container < 0)
		r = 1;
	env = open("./assets/env.png", O_RDONLY);
	if (env < 0)
		r = 1;
	close(h_container);
	close(l_container);
	close(m_container);
	close(env);
	if (r == 1)
		exit_err(ERR_INIT);
}

/*
opens the .cub file and copies its contents into d.level*/
void	read_level(char *path)
{
	int	fd;
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (ft_strncmp(&path[i - 4], ".cub", 5))
		exit_err(ERR_INIT);
	fd = open(path, O_RDONLY);
	if (fd <= 0)
		exit_err(ERR_FD_VAL);
	read_file(fd);
	close(fd);
	/*get_info()*/
	check_asset();
}
