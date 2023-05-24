/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/05/24 15:04:42 by alvachon         ###   ########.fr       */
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

*/

//acts as a pseudo "global" t_master var
//creates the data struct when first called
//returns the previously created data struct on subsequent calls
t_master	*get_master(void)
{
	static t_master	*data; // this static allows this function to return the sate t_data whenever its called (from ANYWHERE in the code)

	if (!data)
		data = ft_calloc(1, sizeof(t_master));

	return (data);
}

//verifies the inputs (arguments and level file) are valid
void	check_inputs(int ac, char **av)
{
	//checks argcount
	if (ac != 2)
		exit_err(ERR_ARG_CO);

	//checks level file's openability
	if (access(av[1], F_OK) || access(av[1], R_OK))
		exit_err(ERR_ARG_OP);
}

int	main(int ac, char **av)
{
	t_master	*data;

	data = get_master(); //		creates the t_master *d struct (first call behaviour)

	check_inputs(ac, av); //	verifies the inputs (arguments and level file) are valid

	read_level(av[1]); //		opens the .cub file and copies its contents into d.level
	printf(">%s<\n\n", data->level); //	0============ DEBUG ============0

	init_map(); //				creates the map grid from the map-info contained in d.level
	//print_tiles(); //					0============ DEBUG ============0

	//	...

	printf("\n");
	return (free_master());
}


/*

	data = get_master() //	creates the t_master *d struct (first call behaviour)

	check_inputs() //		verifies the inputs (arguments and level file) are valid

	read_level() //			opens the .cub file and copies its contents into d.level
		read_file() //			copies the .cub file's contents into d.level
		get_info() //			collects and voids the non-map info from d.level
		check_info() //			verifies the texture paths and floor/ceiling colours

	init_map() //			creates the map grid from the map-info contained in d.level
		check_map() //			verifies each map character and the total map lenght
		build_map()				creates the unconnected tiles for the map grid
		connect_map() //		connects all the map's tiles into a tile grid
		check_flood_fill()		verifies that the map is closed
		init_player() //		creates the player's entity

	init_window()
		init_mlx()
		get_textures()
		check_textures()
		open_window()

	game_loop()
	{
		...
		if (...)
			close_game()
	}



	t_master {

		char		*level
		t_colour	colour x 2
		char		*texture x 4
		char		*last_line_read

	}




*/

