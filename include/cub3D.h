/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/03/27 15:13:55 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// ======== LIBRARIES ======== //

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// ======== DEFINITIONS ======== //

# define ERR_A_CNT	"Input Error : Invalid argument count"
# define ERR_A_VAL	"Input Error : Values have to greater than 0"
# define ERR_P_NONE	"Input Error : I am not, therefore I think not"
# define ERR_P_CNT	"Input Error : Cannot seat this many philosophers"
# define ERR_INIT	"Process Error : Initialization failure"
# define ERR_ACTION	"Process Error : Invalid value given"
# define ERR_THREAD	"Process Error : Thread failure"
# define ERR_MUTEX	"Process Error : Mutex failure"

# define ACT_TAKE	"has taken a fork"
# define ACT_EAT	"is eating"
# define ACT_SLEEP	"is sleeping"
# define ACT_THINK	"is thinking"
# define ACT_DIE	"died"

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