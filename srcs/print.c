/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:46:25 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/10/27 14:28:27 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_concept *info, t_philo *philo, int status_msg)
{
	long int	time_stamp;

	pthread_mutex_lock(&info->print);
	time_stamp = whats_the_time(info);
	if (!info->death_status)
	{
		if (status_msg == 1)
			printf("%lu Philosopher %i got fork\n",
				time_stamp, philo->id + 1);
		if (status_msg == 2)
			printf("%lu Philosopher %i is eating\n",
				time_stamp, philo->id + 1);
		if (status_msg == 3)
			printf("%lu Philosopher %i is sleeping\n",
				time_stamp, philo->id + 1);
		if (status_msg == 4)
			printf("%lu Philosopher %i is thinking\n",
				time_stamp, philo->id + 1);
		if (status_msg == 5)
			printf("%lu Philosopher %i picks up the the fork of philo %i\n",
				time_stamp, philo->id + 1, philo->r_philo->id + 1);
	}
	pthread_mutex_unlock(&info->print);
}

void	print_died(t_concept *info, t_philo *philo)
{
	long int	time_stamp;

	pthread_mutex_lock(&info->print);
	time_stamp = whats_the_time(info) - info->start_time;
	printf("%lu Philosopher %i has died\n", time_stamp, philo->id);
	pthread_mutex_unlock(&info->print);
}