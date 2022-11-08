/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_feast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:07:22 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/08 13:03:25 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//__________________STARTS FEAST: CREATES AND JOINS THREADS___________________//
//note: functions appear in the order they are called;

#include "../includes/philo.h"

static void	join_threads(t_concept *info);

/*/--creates and joins the threads (seperates each philo + starts them off)--/*/
//note: philosophers have been initialised and malloced;
//(1) use 'pthread_create()' to create a thread (everytime it is called), which
//    goes straight into the function 'feasting()';
//(2) use 'whats_the_time()', line x (time.c) to set the time that the philo was
//   'born' (created) (saved in 'long int time_birth_n_last_eaten');
//(3) use 'pthread_create()' to create a thread, which goes straight into the 
//   function 'death()';
//(4) usleep() enables all threads to enter 'feasting()' function and let it begin
//    (pauses the 'start_the_feast()' function) before join_threads is called;
//(5) uses 'join_threads()' to join the threads and bring them back together and 
//   resume 'start_the_feast()' function when their 'feasting()' function finish;
void		start_the_feast(t_concept *info)
{
	int 	i;
	int errchk;

	i = 0;
	errchk = 0;
	while (i < info->no_of_p_f)
	{
		errchk = pthread_create(&info->philo[i].thread, NULL, &feasting, (void *) &info->philo[i]);
		if (errchk != 0)
			fuck_error(info, ERROR_THREAD_CREATION);
		info->philo[i].time_birth_n_last_eaten = whats_the_time(info);
		i++;
	}
	errchk = pthread_create(&info->death, NULL, &death, (void *) info);
		if (errchk != 0)
	usleep(1000);
	join_threads(info);
}

/*/--joins the threads (brings each thread back to main function when done)--/*/
//(1) iterates through n times to join all threads(philosophers) created;
//(2) uses 'pthread_join()', join the philo threads, returns 0 on success to errchk;
//(3) uses 'pthread_join()', join the death thread, returns 0 on success to errchk;

static void	join_threads(t_concept *info)
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