/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seat_philos_at_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:25:29 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/08 11:36:53 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//--------creating (initiating and mallocing) doubly circular linked list to represent the philosophers at the circular table--------//

#include "philo.h"

static void		set_values(t_concept *info);

/* this all happens before any of the threads are created */
void	seat_philos_at_table(t_concept *info)
{
	int i;

	i = 0;
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->no_of_p_f);
	if(info->philo == NULL)
		fuck_error(info, ERROR_MALLOC);
	while(i < info->no_of_p_f)
	{
		if (info->no_of_p_f - 1 == i)
			info->philo[i].r_philo = &info->philo[0];
		else
			info->philo[i].r_philo = &info->philo[i + 1];
		i++;
	}
	set_values(info);
	if (!info->philo)
		fuck_error(info, ERROR_TABLE);
}

static void		set_values(t_concept *info)
{
	int errchk;
	int i;

	i = 0;
	while (i < info->no_of_p_f)
	{
		info->philo[i].id = i + 1;
		info->philo[i].times_eaten = 0;
		errchk = pthread_mutex_init(&info->philo[i].l_fork, NULL);
		info->philo[i].info = info;
		if (errchk != 0)
			fuck_error(info, ERROR_MUTEX_INIT);
		i++;
	}
}