/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feasting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:24:50 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/01 16:37:12 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//===== FEASTING PROCESSES =====//

#include "philo.h"

static void		check_if_died(t_concept *info, t_philo *philo);
static void		chow_down(t_concept *info, t_philo *philo);
static void 	nap_time_n_pondering(t_concept *info, t_philo *philo);

void *feasting(void *voidptr_info)
{
	t_concept	*info;
	int			i;

	info = (t_concept *)voidptr_info;
	i = info->thread_id;
	printf("id: %d\n", (i + 1));
	//if ((i + 1) % 2 == 0)// - maybe dont need this ?
	//	usleep(1000); //time offset to make sure that stuff works?
	while (!info->death_status && info->philo[i].times_eaten != info->times_must_eat)
	{
		chow_down(info, &info->philo[i]);
		nap_time_n_pondering(info, &info->philo[i]);
		check_if_died(info, &info->philo[i]);
	}
	if (info->philo[i].times_eaten == info->times_must_eat)
		fuck_error(info, NOT_ERROR_FULL);
	return (0);
}

static void		pick_up_forks(t_concept *info, t_philo *philo)
{
	int errchk;
	int err_chk;

	errchk = pthread_mutex_lock(&philo->l_fork); //locks this part of the code until unlocked
	if (errchk == 0)
		print(info, philo, 1);
	//if (!ph->r_f)
	//{
	//	ft_usleep(ph->pa->die * 2);
	//	return ;
	//}
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
	printf("forks were put down! errck(put_down_forks): %d + %d\n", errchk, err_chk);
	if (err_chk + errchk != 0)
		fuck_error(info, ERROR_UNLOCK_MUTEX);
}

static void		chow_down(t_concept *info, t_philo *philo)
{
	pick_up_forks(info, philo);
	print(info, philo, 2);
	philo->time_birth_n_last_eaten = whats_the_time(info); //resets time since last eaten
	printf("time_birth_n_last_eaten: %lu\n", philo->time_birth_n_last_eaten);
	custom_usleep(info, info->time_to_eat);
	do_for_x_time(info->time_to_eat);
	philo->times_eaten++;
	printf("times_eaten: %d\n", philo->times_eaten);
	put_down_forks(info, philo);
}


static void 	nap_time_n_pondering(t_concept *info, t_philo *philo)
{
	print(info, philo, 3);
	do_for_x_time(info->time_to_sleep);
	print(info, philo, 4);
}

static void		check_if_died(t_concept *info, t_philo *philo)
{
	if (philo->time_since_eaten >= info->time_to_die)
	{
		print_died(info, philo);
		fuck_error(info, ERROR_DIED);
		info->death_status = 1;
	}
}