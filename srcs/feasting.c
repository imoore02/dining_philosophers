/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feasting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:24:50 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/07 22:15:19 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//______ FEASTING PROCESSES: LOOPS THROUGH EATING, SLEEPING, N THINKING ______//
//note: functions appear in the order they are called;

#include "../includes/philo.h"

static void		eat_sleep_think(t_concept *info, t_philo *philo);
static void		pick_up_forks(t_concept *info, t_philo *philo);
static void 	put_down_forks(t_concept *info, t_philo *philo);

/*/--simultaneuously(not literally but more like parallel) loops through eating,
//   sleeping and thinking for all philos--/*/
//(1) must typecast void pointer philo into philo and init 't_concept *info'
//	  using philo->info pointer;
//(2) use modulo 2 to get all even number philos to pause; creating a 
//    staggering effect -> prevents collisions of mutex locking;
//(3) while conditions are met (philo isnt dead or full) -> 'eat_sleep_think()'
//    will be called
//note: if input was not entered for info->times_must_eat then it is set to -1 
//      ('initialise()', line x (initialise.c)), and therefore the fullness 
//      condition will be ignored as info->times_must_eat (-1) will never equal
//      philo->times_eaten (which starts at 0);
void *feasting(void *voidptr_philo)
{
	t_philo	*philo;
	t_concept *info;
	
	philo = (t_philo *)voidptr_philo;
	info = philo->info;
	if (philo->id % 2 == 0)
		usleep(1000);
	while ((philo->times_eaten != info->times_must_eat) && !info->death_status)
	{
		eat_sleep_think(info, philo);
	}
	return (0);
}

/*/--the lifecycle process--/*/
//(1) 'pick_up_forks' to lock mutexes;
//(2) once mutex is locked variable 'philo->times_eaten' is altered;
//(3) calls 'print()', line 17 (print.c); eating message;
//(4) sets the 'philo->time_birth_n_last_eaten' to be the current time;
//(5) calls 'do_for_x_time()', line x (time.c) to 'eat' (i.e hold the forks 
//    / keep the mutexes locked) for 'time_to_eat';
//(6) 'put_down_forks' unlocks the mutexes;
//(7) 'print()' will print a sleep message;
//(7) after forks are put down 'do_for_x_time()' will 'sleep' for the alotted
//    'info->time_to_sleep' input;
//(8) 'print()' will print a think message; there is no input for time to think
//    so this can go on for whatever length of time;
static void		eat_sleep_think(t_concept *info, t_philo *philo)
{
	pick_up_forks(info, philo);
	philo->times_eaten++;
	print(info, philo, 2);
	philo->time_birth_n_last_eaten = whats_the_time(info);
	do_for_x_time(info, info->time_to_eat);
	put_down_forks(info, philo);
	print(info, philo, 3);
	do_for_x_time(info, info->time_to_sleep);
	print(info, philo, 4);
}

/*/--picks up the forks AKA locks the fork mutexes--/*/
//(1) locks 'pthread_mutex l_fork' using pthread_mutex_lock; will return 0 to errchk on success;
//(2) 'print()' will print a got left fork message;
//(3) lock 'pthread_mutex l_fork' of 'philo->r_philo' (the fork of the philosopher to the right'
//    using pthread_mutex_lock; will return 0 to errchk on success;
//(4) 'print()' will print a got right fork message;
static void	pick_up_forks(t_concept *info, t_philo *philo)
{
	int errchk;
	int err_chk;

	errchk = pthread_mutex_lock(&philo->l_fork);
	if (errchk != 0)
		fuck_error(info, ERROR_LOCK_MUTEX);
	print(info, philo, 1);
	err_chk = pthread_mutex_lock(&philo->r_philo->l_fork);
	if (err_chk != 0)
		fuck_error(info, ERROR_LOCK_MUTEX);
	print(info, philo, 5);
}

/*/--puts down the forks AKA unlocks the fork mutexes--/*/
//(1) unlocks 'pthread_mutex l_fork' using pthread_mutex_unlock; will return 0 to errchk on success;
//(2) unlock 'pthread_mutex l_fork' of 'philo->r_philo' (the fork of the philosopher to the right'
//    using pthread_mutex_unlock; will return 0 to errchk on success;
static void put_down_forks(t_concept *info, t_philo *philo)
{
	int errchk;
	int err_chk;

	errchk = pthread_mutex_unlock(&philo->l_fork);
	if (errchk != 0)
		fuck_error(info, ERROR_LOCK_MUTEX);
	err_chk = pthread_mutex_unlock(&philo->r_philo->l_fork);
	if (err_chk != 0)
		fuck_error(info, ERROR_LOCK_MUTEX);
}