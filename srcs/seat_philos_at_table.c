/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seat_philos_at_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:25:29 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/01 16:07:27 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//--------creating (initiating and mallocing) doubly circular linked list to represent the philosophers at the circular table--------//

#include "philo.h"

static void		set_values(t_concept *info, int i);

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
		//printf("i: %d\n", i);
		set_values(info, i);
		//if (info->no_of_p_f == 1) //WHAT ARE YOU SUPPPOSED TO DO WHEN THERE IS ONLY ONE PHILO	
		if (info->no_of_p_f - 1 == i) //at the last philo - how u make it circular 
			info->philo[i].r_philo = &info->philo[0]; //success
		else
			info->philo[i].r_philo = &info->philo[i + 1]; //success
		//printf("info->philo[i].r_philo: %p, &info->philo[0]: %p\n ", info->philo[i].r_philo, &info->philo[0]);
		//printf("no_of_philo - 1: %d\n", info->no_of_p_f - 1);
		//printf("info->philo[i].r_philo: %p, &info->philo[%d]: %p\n ", info->philo[i].r_philo, i + 1, &info->philo[i + 1]);
		i++;
	}
	if (!info->philo)
		fuck_error(info, ERROR_TABLE);
}

static void		set_values(t_concept *info, int i)
{
	int errchk;
	
	info->philo[i].id = i + 1; //philo ids start at 1;
	//printf("philo id: %d\n", info->philo[i].id);
	info->philo[i].times_eaten = 0;
	errchk = pthread_mutex_init(&info->philo[i].l_fork, NULL);
	if (errchk != 0)
		fuck_error(info, ERROR_MUTEX_INIT);
}