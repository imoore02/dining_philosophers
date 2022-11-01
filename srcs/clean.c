/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:04:32 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/01 15:36:47 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//________CLEANS UP: PRINTS ERRORS(if any), FREES AND EXITS PROGRAM/EXECUTION_________//

#include "philo.h"

static void	clean_shit_up(t_concept *info);

void		fuck_error(t_concept *info, char *errorcode)
{
	printf("%s", errorcode);
	clean_shit_up(info);
	exit(-1);
}

static void		kill_philos(t_concept *info)
{
	int i;
	int errckr;

	i = 0;
	while (i < info->no_of_p_f)
	{
		pthread_mutex_unlock(&info->philo[i].l_fork);
		errckr = pthread_mutex_destroy(&info->philo[i].l_fork);
		printf("errchk (kill_philos): %d\n", errckr);
		if (errckr != 0)
			printf("%s", ERROR_MUTEX_DESTROY_FORK);
		i++;
	}
	free(info->philo);
}

static void	clean_shit_up(t_concept *info)
{
	int errckr;

	if (info)
	{
		if (info->philo)
			kill_philos(info);
		errckr = pthread_mutex_destroy(&info->print);
		//printf("errchk (clean_shit_up): %d\n", errckr);
		if (errckr != 0)
			printf("%s", ERROR_MUTEX_DESTROY);
		free(info);
		info = NULL;
	}
}