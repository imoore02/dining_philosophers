/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:32:49 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/08 13:17:03 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//_____________________TIME: ALL TIME RELATED FUNCTIONS______________________//
//note: functions appear in the order they are called;

#include "../includes/philo.h"

/*/--returns the current time in milliseconds--/*/
//note: 'gettimeofday' gives: (1 - current_time.time_t tv_sec) the timer in 
//      seconds since 00:00:00 jan 1st 1970, (2 - current_time.suseconds 
//      tv_usec) additonal microseconds after no of microseconds since timer
//      calculation;
//note: get 'time' convert both to milliseconds (long int) and add them together
//note: struct timeval = struct representing a simple calendar time or an 
//     elapsed time - sub-second resolution sys?time.h - members: time_t, tv_sec;
//note: 'gettimeofday()' gets systems clock time - expressed in microseconds
//      since 00:00:00 jan 1st 1970;
//note: must convert both to milliseconds (since the epoch) (line 35);
long int	whats_the_time(t_concept *info)
{
	struct timeval		current_time;
	int 				errchk;
	long int			time;

	errchk = gettimeofday(&current_time, NULL); 
	if (errchk == -1)
		fuck_error(info, ERROR_TIME);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

/*/--suspends execution for 'long int time' milliseconds--/*/
//note: input for 'usleep()' is in useconds/microseconds (1000 micro = 1 milli);
//note on operation: the while loop is necessary as usleep is usually inaccurate,
//                   and generally varies by a couple milliseconds, but overtime
// 					 even the slightest variation would kill a philosopher; also
//					 need to check if its died;
//(1) gets time that the function was called using 'whats_the_time()', 
//    and returns it to t;
//(2) while philo isnt dead (need to check this constantly as death message cant
//    be printed more than 10 milliseconds after) after death condition is met;
//(3) 'int i' represents the amount of time elapsed since the function was
//    first called; if the time elapsed is >= to how long its supposed to go for it
//    will break and execution of fucntion that call it will resume;
//(4) if not broken -> 'usleep()' will pause function for 0.1 millisecond;
void	do_for_x_time(t_concept *info, long int time)
{
	int t;
	int i;
	int errchk;
	
	t = whats_the_time(info);
	while (!info->death_status)
	{
		i = whats_the_time(info) - t;
		if (i >= time)
			break ;
		errchk = usleep(100);
		if (errchk != 0)
			fuck_error(info, ERROR_USLEEP);
	}
}