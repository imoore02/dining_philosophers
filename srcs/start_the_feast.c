/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_feast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:07:22 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/02 12:37:38 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_concept *info);

//--philosophers have been initialised and malloced--//
void		start_the_feast(t_concept *info)
{
	int 	i;
	int errchk;

	i = 0;
	errchk = 0; //get rid of this laterx
	while (i < info->no_of_p_f)
	{
		info->thread_id = i; //(0 - N)
		errchk = pthread_create(&info->philo[i].thread, NULL, &feasting, (void *) info); //this is always successfull
		if (errchk != 0)
			fuck_error(info, ERROR_THREAD_CREATION);
		info->philo[i].time_birth_n_last_eaten = whats_the_time(info);
		printf("thread %d errchk (p_thread create success @ %lu, errchk: %d\n", info->thread_id, info->philo[i].time_birth_n_last_eaten, errchk);
		errchk = usleep(4000); //offsets time between thread creations;????? - this is in micro(u)seconds - for some reason it will take 2 more milliseconds than what is entered
		if (errchk != 0)
			fuck_error(info, ERROR_USLEEP);
		i++;
	}
	usleep(10000); //just to give it a bit of time to do things; - helpful for destroying mutexes properly??
	join_threads(info);
}

static void	join_threads(t_concept *info)
{
	int i;
	int errchk;
	
	i = 0;
	errchk = 0; //get rid of this later
	while (i < info->no_of_p_f)
	{
		errchk = pthread_join(info->philo[i].thread, NULL);
		if (errchk != 0)
			fuck_error(info, ERROR_THREAD_JOIN);
		else
			printf("successful joining!\n");
		i++;
	}
}