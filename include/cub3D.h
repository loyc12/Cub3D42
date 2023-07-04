/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/07/04 15:28:31 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ======== LIBRARIES ======== //

# include "../MLX42/include/MLX42/MLX42.h"
# include "../Libft42/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <math.h>

# include "defs.h"
# include "enums.h"
# include "funcs.h"
# include "structs.h"

#endif // CUB3D_H

/*

	0======== BUGS ========0

can sometime see through corners
accepts colours without blue (ex: C 0,0)

	0======== IDEAS ========0

attach current tile to entities/player
prevent placing tiles on entities
be able to place walls on non-tiles (map borders)
respawn in proper direction
use mouse to turn cameras
add a minimap
add music & sounds
give voids its own texture

*/