/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feasting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:24:50 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/02 14:13:26 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//===== FEASTING PROCESSES =====//

#include "philo.h"

//static void		check_if_died(t_concept *info, t_philo *philo);
static void		chow_down(t_concept *info, t_philo *philo);
static void 	nap_time_n_pondering(t_concept *info, t_philo *philo);

void *feasting(void *voidptr_info)
{
	t_concept	*info;
	int i;
	
	info = (t_concept *)voidptr_info;
	i = info->thread_id;
	printf("id(feasting): %d\n", info->thread_id);
	while (info->philo[i].times_eaten != info->times_must_eat)
	{
		//printf("in the loop %d\n", i);
		chow_down(info, &info->philo[i]);
		nap_time_n_pondering(info, &info->philo[i]);
		//check_if_died(info, &info->philo[i]);
	}	
	if (info->philo[i].times_eaten == info->times_must_eat)
		printf("Philosopher %d is full!\n", i + 1);
	return (0);
}

static void		pick_up_forks(t_concept *info, t_philo *philo)
{
	int errchk;
	int err_chk;

	//printf("times already eatn: %d\n", philo->times_eaten);
	//printf("about to try pick up mutex\n");
	errchk = pthread_mutex_lock(&philo->l_fork); //locks this part of the code until unlocked
	if (errchk == 0)
		print(info, philo, 1);
	err_chk = pthread_mutex_lock(&philo->r_philo->l_fork);
	if (err_chk == 0)
		print(info, philo, 5);
	else 
		fuck_error(info, ERROR_LOCK_MUTEX);
}

static void		put_down_forks(t_concept *info, t_philo *philo)
{
	int errchk;
	int err_chk;

	errchk = pthread_mutex_unlock(&philo->l_fork); //locks this part of the code until unlocked
	err_chk = pthread_mutex_unlock(&philo->r_philo->l_fork);
	//printf("errchk: %d\n", errchk);
	//printf("forks were put down! errck(put_down_forks): %d + %d\n", errchk, err_chk);
	if (err_chk + errchk != 0)
		fuck_error(info, ERROR_UNLOCK_MUTEX);
}

static void		chow_down(t_concept *info, t_philo *philo)
{
	pick_up_forks(info, philo);
	print(info, philo, 2);
	philo->time_birth_n_last_eaten = whats_the_time(info); //resets time since last eaten
	//printf("time_birth_n_last_eaten: %lu\n", philo->time_birth_n_last_eaten);
	//my_usleep(info, info->time_to_eat);
	do_for_x_time(info, info->time_to_eat);
	philo->times_eaten++;
	//printf("times_eaten: %d\n", philo->times_eaten);
	put_down_forks(info, philo);
}


static void 	nap_time_n_pondering(t_concept *info, t_philo *philo)
{
	print(info, philo, 3);
	do_for_x_time(info, info->time_to_sleep);
	print(info, philo, 4);
}