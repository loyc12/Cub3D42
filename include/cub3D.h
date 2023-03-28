/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/03/28 11:46:18 by llord            ###   ########.fr       */
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

// ======== DEFINITIONS ======== //

# define ERR_A_CNT	"Input Error : Invalid argument count"
# define ERR_INIT	"Process Error : Initialization failure"
# define ERR_ACTION	"Process Error : Invalid value given"

# define ADRS		(void **)&
# define ADRS2		(void ***)&

// ======== ENUM STATES ======== //

enum e_mstate
{
	MSTATE_ERROR	= -1,
	MSTATE_STARTING	= 0,
	MSTATE_RUNING	= 1,
	MSTATE_ENDING	= 2
};

// ======== STRUCTS ======== //

typedef struct s_meta	t_meta;

typedef struct s_tile
{
	int	tile_id;
}			t_tile;

typedef struct s_meta
{

	int	state;
}		t_meta;

// ======== FUNCTIONS ======== //

//from main

#endif