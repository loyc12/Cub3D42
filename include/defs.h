/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/06/16 10:17:24 by llord            ###   ########.fr       */
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
# define MAX_CHAR_COUNT (int)8192 //lvl file size
# define MAX_MAP_SIZE (int)64 //	map size (in tiles)
# define PLAYER_RADIUS (double)0.2
# define ASSET_COUNT (int)4 //		asset count
// DISPLAY
# define SCREEN_WIDTH (int)1536
# define SCREEN_HEIGHT (int)1152
# define PIXEL_SIZE (int)2 //		(1 to 32)
// VIEW
# define PLAYER_FOV (double)70 //	(10 to 100)	field of view
# define S_FACTOR (double)0.6 //	(0 to 1)	shading range

#endif // DEFS_H
