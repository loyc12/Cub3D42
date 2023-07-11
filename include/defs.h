/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/07/11 17:11:05 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

// ======== DEFINITIONS ======== //

// ERROR FILE
# define ERR_ARG_COUNT	"Input Error : Invalid argument count"
# define ERR_FILE_LEVEL	"File Error : Invalid level file path"
# define ERR_FILE_ASSET	"File Error : Invalid asset file path"
# define ERR_FILE_CUBE	"File Error : Level file is not a .cub"
# define ERR_FILE_PNG	"File Error : Asset file is not a .png"
# define ERR_FILE_SIZE	"File Error : Level file is too large"
# define ERR_FILE_SPECS	"File Error : Level specification missing"
# define ERR_FILE_COLOR	"File Error : Invalid colour code"

// ERROR MAP
# define ERR_MAP_SIZE	"Map Error : Map is too large"
# define ERR_MAP_PLAYER	"Map Error : Map has an invalid number or players"
# define ERR_MAP_CHAR	"Map Error : Map uses invalid symbols"
# define ERR_MAP_BOUND	"MAP Error : Map is not enclosed"

// ======== SHORTCUTS ======== //

// POINTERS
# define ADRS (void **)&
# define ADRS2 (void ***)&

// BYTE PER PIXEL, = sizeof(int32_t)
# define BPP 4

// ======== CONSTANTS ======== //

// SPEED REF (1 tile ~= 3m)
# define WALK_SPEED (double)0.05
# define TURN_SPEED (double)1.5
# define RUN_FACTOR (double)2.5

// SIZE
# define MAX_CHAR_COUNT (int)8192 //	lvl file size
# define MAX_MAP_SIZE (int)64 //		map size (in tiles)
# define PLAYER_RADIUS (double)0.2
# define ASSET_COUNT (int)4 //			asset count

// DISPLAY
# define SCREEN_WIDTH (int)1536
# define SCREEN_HEIGHT (int)1152
# define PIXEL_SIZE (int)4 //			(1 to 32)
//# define COLOUR_DEF (int)1 //			(1 to 32) slows rendering by ~10%

// VIEW
# define PLAYER_FOV (double)70 //		(10 to 100)	field of view
# define SHADE_DISTANCE (double)32 //	(0 to 100)	wall shading distance (inverse strenght)
# define SHADE_FACTOR (double)0.66 //	(0 to 1)	floor/ceiling shading strenght
# define INV_SHADE_C (int)1 //			(0 or 1)	(inverted ceiling shading creates a better sky effect)
# define INV_SHADE_F (int)0 //			(0 or 1)

#endif // DEFS_H
