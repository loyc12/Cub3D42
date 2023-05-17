/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/05/17 16:14:06 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	int				j;
	unsigned char	ch;

	i = 0;
	j = 0;
	ch = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			j = i;
		i++;
	}
	if (s[i] == '\0' && ch == 0)
		return ((char *)s + i);
	else if (j > 0 || (j == 0 && s[j] == ch))
		return ((char *)s + j);
	return (NULL);
}

void	ft_copy_next(char *s1, char *s2)
{
	int	i;

	i = 0;
	printf("# # # #  \n");
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

int	ft_get_line(char *container, char **line)
{
	int		len;
	int		i;
	int		nl;
	char	*str;

	len = 0;
	i = 0;
	printf("* * * \n");
	while (container[len] && container[len] != '\n')
		len++;
	nl = 0;
	printf("* * * \n");
	if (container[len] == '\n')
		nl = 1;
	printf("* * * \n");
	str = ft_calloc(len + nl + 1, sizeof(char));
	if (str == NULL)
		return (-1);
	printf("* * * \n");
	while (i < (len + nl))
	{
		str[i] = container[i];
		i++;
	}
	printf("ft_strjoin bug * * \n");
	*line = ft_strjoin(*line, str);
	printf("2 * * \n");
	if (line == NULL)
		return (-1);
	printf("* * * \n");
	ft_copy_next(container, &container[len + nl]);
	return (nl);
}

char	*ft_free(char **line)
{
	if (*line != NULL)
		free(*line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	container[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			ret;
	int			readed;

	line = NULL;
	ret = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &container, 0) < 0)
		return (0);
	while (ret == 0)
	{
		ret = ft_get_line(container[fd], &line);
		if (ret == -1)
			return (ft_free(&line));
		if (ret == 0)
		{
			readed = read(fd, container[fd], BUFFER_SIZE);
			if (readed == 0 && *line)
				ret = 1;
			else if (readed <= 0)
				return (ft_free(&line));
			container[fd][readed] = '\0';
		}
	}
	return (line);
}

//writes an error message followed by \n
//returns 1 if the message is non empty
int	msg_error(char *err)
{
	int	i;

	i = -1;
	while (err[++i] != '\0')
		write (2, &err[i], 1);
	write (2, "\n", 1);
	if (err[0])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	verify_type(char *file)
{
	file = ft_strrchr(file, '.');
	while (ft_strlen(file) != 4)
		file = ft_strrchr(file, '.');
	if (ft_strncmp(file, ".cub", 3) != 0)
		return (1);
	return (0);
}

int	verify_access(char *file, t_data *data, t_fd code)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (1);
	}
	printf(":::::\n");
	if (code == CUB)
	{
		printf(":::::\n");
		data->fd = fd;
		printf(":::::\n");
	}
	if (code == NO)
		data->fd_no = fd;
	if (code == SO)
		data->fd_so = fd;
	if (code == WE)
		data->fd_we = fd;
	if (code == EA)
		data->fd_ea = fd;
	return (0);
}

int	check_texture_path(char *cmd, t_data *data, t_fd code)
{
	cmd += 3;
	if (cmd[0] != '.' || cmd[1] != '/')
		return (3);
	if (verify_access(cmd, data, code) != 0)
		return (4);
	return (0);
}

int	verify_file(t_data *data)
{
	char	*line;
	int		i;
	int		r;

	line = NULL;
	i = 0;
	r = 0;
	printf(":::::\n");
	line = get_next_line(data->fd);
	printf(":::::\n");
	if (!line)
	{
		close (data->fd);
		return (1);
	}
	else
		i += 1;
	if (i == 1 && line[0] == 'N' && line[1] == 'O')
		r = check_texture_path(line, data, NO);
	else if ((i == 2 && line[0] == 'S' && line[1] == 'O'))
		r = check_texture_path(line, data, SO);
	else if ((i == 3 && line[0] == 'W' && line[1] == 'E'))
		r = check_texture_path(line, data, WE);
	else if ((i == 3 && line[0] == 'E' && line[1] == 'A'))
		r = check_texture_path(line, data, EA);
	else
		return (2);
	return (r);
}

int	verify_input(int ac, char **av, t_data *data)
{
	int		r;

	if (ac != 2)
		return (msg_error(ARG_COUNT));
	printf("--\n");
	if (verify_type(av[0]) != 0)
		return (msg_error(FILE_TYPE));
	printf("--\n");
	if (verify_access(av[0], data, CUB) != 0)
		return (msg_error(FILE_ACCESS));
	printf("--\n");
	r = verify_file(data);
	printf("--\n");
	if (r == 1)
		return (msg_error(FILE_CONTENT));
	if (r == 2)
		return (msg_error(FILE_RULE));
	if (r == 3)
		return (msg_error(FILE_PATH));
	if (r == 4)
		return (msg_error(RESSOURCE));
	printf("Input is verified\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	printf("--\n");
	verify_input(ac, av + 1, data);

	data = get_data(); //			creates the t_data *d struct when first called, accesses it after
	get_lvl(av[1]); //			opens and copies the lvl file into d->lvl

	//printf(">%s<\n", d->lvl); //						DEBUG

	//init_level(); //			should remove the non-map data (replace it by \n (?))

	init_map(data); //				checks and gets the map info from the .cub file (move into init_lvl (?))
	connect_tiles(); //			connects tiles with their neighbours
	flood_check(data->spawn);
	//init_player()

	//print_tiles(); //									DEBUG

	//init_gfx(); //			initializes the mlx and its textures
	//	init_window();
	//	init_textures();

	//launch_game(); //			main game loop function
	//	check_moves
	//	re_display
	printf("\n");
	return (free_data());
}
