/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:46:25 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/08 11:35:33 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//________________________PRINTING/OUTPUT MESSAGES____________________________//
//note: functions appear in the order they are called;

#include "../includes/philo.h"

static char	*set_colours(int n);

/*/--prints a message for when a philo dies--/*/
//notes: locks 'pthread_mutex write' to stop any other thread/philos trying to 
//       write at the same time and scrambling the messages; unlock when done;
// 		 time time_stamp is the elapsed program run time (i.e how long it took
//       to philo to do whatever from the start of the program)  
void	print(t_concept *info, t_philo *philo, int status_msg)
{
	long int	time_stamp;
	char 		*colour;
	
	pthread_mutex_lock(&info->print);
	colour = set_colours(philo->id);
	time_stamp = whats_the_time(info) - info->start_time;
	if (!info->death_status)
	{
		if (status_msg == 1)
			printf("%s%lu Philosopher %i got fork \033[0m\n",
				colour, time_stamp, philo->id);
		if (status_msg == 2)
			printf("%s%lu Philosopher %i is eating (eaten %d times) \033[0m\n",
				colour, time_stamp, philo->id, philo->times_eaten);
		if (status_msg == 3)
			printf("%s%lu Philosopher %i is sleeping\033[0m\n",
				colour, time_stamp, philo->id);
		if (status_msg == 4)
			printf("%s%lu Philosopher %i is thinking\033[0m\n",
				colour, time_stamp,  philo->id);
		if (status_msg == 5)
			printf("%s%lu Philosopher %i picks up the the fork of philo %i\n",
				colour, time_stamp, philo->id, philo->r_philo->id);
	}
	pthread_mutex_unlock(&info->print);
}

/*/--prints a message for when a philo dies--/*/
//notes: locks 'pthread_mutex write' to stop any other thread/philos trying to 
//       write at the same time and scrambling the messages; unlock when done;
// 		 time time_stamp is the elapsed program run time (i.e how long it took
//       to philo to die from the start of the program)    
void	print_died(t_concept *info, t_philo *philo)
{
	long int	time_stamp;

	time_stamp = whats_the_time(info) - info->start_time;
	pthread_mutex_lock(&info->print);
	printf("%s%lu Philosopher %i has died\n", philo->colour, time_stamp, philo->id);
	pthread_mutex_unlock(&info->print);
}

//--sets different colours for philo messages--//
//operation: a philo will be assigned a colour depending on the modulo
//           of its id by 5;
//notes: buy placing any one of these char *strings at the start of an output
//       message you change its colour; using '\033[0m\n' will change it back;
static char	*set_colours(int n)
{
	if (n % 5 == 0)
		return("\033[0;35m");
	else if (n % 5 == 1)
		return("\033[0;36m");
	else if (n % 5 == 2)
		return("\033[0;34m");
	else if (n % 5 == 3)
		return("\033[0;32m");
	else if (n % 5 == 4)
		return("\033[0;31m");
	else
		return("\033[0;30m");
}