/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 12:51:07 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

// ======== DEFINITIONS ======== // RENAME THEM TO MORE CONSCISE AND READABLE NAMES

# define ERR_INIT		"Process Error : Initialization failure" //			internal error
# define ERR_ARG_COUNT	"Input Error : Invalid argument count"

# define ERR_FILE_LEVEL	"File Error : Invalid level file path" //			inexistant file or invalid perms
# define ERR_FILE_CUBE	"File Error : Level file is not a .cub"
# define ERR_FILE_SIZE	"File Error : Level file is too large"
# define ERR_FILE_SPECS	"File Error : Level specification missing" //		wall assets paths or ceiling & floor colours
# define ERR_FILE_ASSET	"File Error : Invalid asset file path" //			inexistant file or invalid perms
# define ERR_FILE_COLOR	"File Error : Invalid colour code"

# define ERR_MAP_SIZE	"Map Error : Map is too large"
# define ERR_MAP_PLAYER	"Map Error : Map has an invalid number or players"
# define ERR_MAP_CHAR	"Map Error : Map uses invalid symbols"
# define ERR_MAP_BOUND	"MAP Error : Map is not enclosed"

// ======== SHORTCUTS ======== //

# define ADRS	(void **)&
# define ADRS2	(void ***)&
# define BPP 	4 // sizeof(int32_t)

// ======== CONSTANTS ======== //

//speeds (1 tile ~= 3m)
# define WALK_SPEED		(double)0.20 //	walking speed (in tile/tic)
# define TURN_SPEED		(double)3.0 //	turning speed (in deg/tic)
# define RUN_FACTOR		(double)2.5 //	running speed (in tile/tic)

//sizes
# define MAX_CHAR_COUNT	(int)8192 //	maximum level file size (in chars)
# define MAX_MAP_SIZE	(int)64 //		maximum horizontal/vertical map size (in tiles)

# define PLAYER_RADIUS	(double)0.2
# define ASSET_COUNT	(int)4 //		asset count
//# define ASSET_SIZE		(int)64 //		asset size (in pixels)

//display
# define SCREEN_WIDTH	(int)1536
# define SCREEN_HEIGHT	(int)1152
# define PIXEL_SIZE		(int)3 //		(1 to 32)	size of virtual pixels (in real pixels)

# define PLAYER_FOV		(double)70 //	(10 to 100)	field of view
# define S_FACTOR		(double)0.5 //	(0 to 1)	how much shading the walls, floor and ceiling get

#endif // DEFS_H
