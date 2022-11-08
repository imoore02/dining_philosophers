/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:32:49 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/07 19:18:02 by isobelmoore      ###   ########.fr       */
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
	return (time);
}

//---returns the time (in milliseconds) that the program has been running--//
long int	elapsed_run_time(t_concept *info)
{
	long int	total_time;

	total_time = whats_the_time(info) - info->start_time;
	return (total_time);
}

void	do_for_x_time(t_concept *info, long int time)
{
	int t;
	int i;
	
	t = whats_the_time(info);
	while (!info->death_status)
	{
		i = whats_the_time(info) - t;
		if (i >= time)
			break ;
		usleep(100);
	}
}