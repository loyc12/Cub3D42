/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/03/28 09:32:46 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//entrypoint function
int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	printf("\n   Hello wooooorld!\n");
	printf("   Program to work and not to feeeEEEeeel\n");
	printf("   Don't even know if this is reeeEEEaaal\n");
	printf("   Hello wooooorld...\n\n");
/*
	int		exit_status;
	t_meta	*m;

	if (ac != 2) //checks for a proper argcount
		return (throw_error(ERR_A_CNT));

	m = calloc(1, sizeof(t_meta)); //CHAGNE TO FT_CALLOC !!!!!!
	if (init_meta(m, av)) //initilizes t_meta and all its sub structs/things
		return (free_null(ADRS m), throw_error(ERR_INIT));

	exit_status = run_philo(m); //runs the main logic loop

	free_all(m);
	return (exit_status);
*/
}
