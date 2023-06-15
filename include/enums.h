/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:56:01 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 14:55:08 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

// ======== ENUM STATES ======== //

//machine states (where the program is at execution wise)
typedef enum e_mstate
{
	MSTATE_ERROR	= -1,
	MSTATE_STARTING	= 0,
	MSTATE_RUNNING	= 1,
	MSTATE_RESTART	= 2,
	MSTATE_ENDING	= 3
}			t_mstate;

//texture ID (the index of the texture in the asset array)
typedef enum e_tid
{
	TID_1_NORTH	= 0,
	TID_1_EAST	= 1,
	TID_1_SOUTH	= 2,
	TID_1_WEST	= 3
}			t_tid;

//tile type (how should we interact/display this tile)
typedef enum e_ttype
{
	TTYPE_ERROR	= -1,
	TTYPE_ROOM	= 0,
	TTYPE_WALL	= 1
}			t_ttype;

#endif //	ENUMS_H