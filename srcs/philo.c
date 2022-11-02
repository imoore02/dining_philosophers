/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:37:15 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/02 13:38:50 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//--running process-//
//(1) memory allocates for a structure (t_concept *info) that will contain all necessary information for the programs execution;
//(2) initialises the structure -> sets values to a default, for t_philo *table_of_philos inside t_concept *info, you must memory allocate and initialise these as well;
int main(int argc, char **argv)
{
	t_concept *info;

	info = NULL;
	if (argc == 5 || argc == 6)
	{
		info = (t_concept *)malloc(sizeof(t_concept));
		if (info == NULL)
			fuck_error(info, ERROR_MALLOC);
		initialise(argc, argv, info);
		start_the_feast(info);
	}
	else
		fuck_error(info, ERROR_INPUT_INVALID);
	return (0);
}