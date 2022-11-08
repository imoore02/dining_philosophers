/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_feast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:07:22 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/07 19:09:00 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_concept *info);

//--philosophers have been initialised and malloced--//
void		start_the_feast(t_concept *info)
{
	int 	i;
	int errchk;

	i = 0;
	errchk = 0;
	while (i < info->no_of_p_f)
	{
		info->thread_id = i;
		errchk = pthread_create(&info->philo[i].thread, NULL, &feasting, (void *) &info->philo[i]);
		if (errchk != 0)
			fuck_error(info, ERROR_THREAD_CREATION);
		info->philo[i].time_birth_n_last_eaten = whats_the_time(info);
		i++;
	}
	errchk = pthread_create(&info->death, NULL, &death, (void *) info);
		if (errchk != 0)
	usleep(1000); //just to give it a bit of time to do things; - helpful for destroying mutexes properly?? 10,000
	join_threads(info);
}

void	join_threads(t_concept *info)
{
	int i;
	int errchk;
	
	i = 0;
	errchk = 0;
	while (i < info->no_of_p_f)
	{
		errchk = pthread_join(info->philo[i].thread, NULL);
		if (errchk != 0)
			fuck_error(info, ERROR_THREAD_JOIN);
		i++;
	}
	errchk = pthread_join(info->death, NULL);
	if (errchk != 0)
		fuck_error(info, ERROR_THREAD_JOIN);
}