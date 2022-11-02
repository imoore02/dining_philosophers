/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:32:49 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/02 14:15:48 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//---returns the current time in milliseconds---//
//notes: 'gettimeofday' gives: (1 - current_time.time_t tv_sec) the timer in seconds since 00:00:00 jan 1st 1970, (2 - current_time.suseconds tv_usec) additonal microseconds after no of microseconds since timer calculation;
//notes: to get 'time' convert both to milliseconds (long int) and add them together
long int	whats_the_time(t_concept *info)
{
	struct timeval		current_time; //struct representing a simple calendar time or an elapsed time - sub-second resolution sys?time.h - members: time_t, tv_sec
	int 				errchk;
	long int			time;

	errchk = gettimeofday(&current_time, NULL); //gets systems clock time - expressed in microseconds since 00:00:00 jan 1st 1970
	if (errchk == -1)
		fuck_error(info, ERROR_TIME);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000); //converting both to milliseconds (since the epoch)
	//printf("time(whats the time): %lu\n", time);
	return (time);
}

//---returns the time (in milliseconds) that the program has been running--//
long int	elapsed_run_time(t_concept *info)
{
	long int	total_time;

	total_time = whats_the_time(info) - info->start_time;
	return (total_time);
}
/*
//---if philo has eaten in half the time they have until they starve, they will wait half a millisecond to try to eat again--//
//notes: prevents starvatiion on odd number of philosophers;
static void	hesitate(t_concept *info)
{
	int errchk;

	errchk = 0;
	if((elapsed_run_time(info) - info->start_time) < info->time_to_die / 2 )
		errchk = usleep(500); //suspends execution for microsecond intervals
		if (errchk == -1)
			fuck_error(info, ERROR_USLEEP);
}

void		do_for_x_time(long int time) //input the milliseconds to do this for
{
	int t;

	t = time * 1000;
	usleep(t); //seconds to do the thing for according to the variable
}*/

void	do_for_x_time(t_concept *info, long int time)
{
	int t;

	t = time * 1000;
	printf("%d\n", info->death_status);
	while (1)
	{
		usleep(t);
		break ;
	}
}