/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:04:32 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/07 20:35:34 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//____CLEANS UP: PRINTS ERRORS(if any), FREES AND EXITS PROGRAM/EXECUTION____//
//note: functions appear in the order they are called;

#include "../includes/philo.h"

static void		clean_shit_up(t_concept *info);
static void		kill_philos(t_concept *info);

/*/--main error function--/*/
//(1) 'errorcodes'(macrocs) are stored in the header file (philo.h);
//(2) exit code -1 (EXIT_FAILURE) will show that there was abnormal behaviour 
//    in the program causing it to exit;
void		fuck_error(t_concept *info, char *errorcode)
{
	printf("%s", errorcode);
	clean_shit_up(info);
	exit(EXIT_FAILURE);
}

/*/--frees the memory put aside for t_concept *info + t_concept *philo(s)--/*/
//operation:
//(1) checks if 't_concept *info' exists (i.e if it is not NULL)
//(2) checks if 't_philo *philo' exists (as above) -> if so calls 'kill_philos'
//    this needs to be done seperately because its memory was allocated seperately
//    so you neeed to do a mirror-like freeing/nulling to your allocating
//(3) destroys the 'pthread_mutex print' that was inside 't_concept *info' 
//	  (initalised in 'initialise()', line x, (initialise.c))
//(4) if 'pthread_mutex_destroy()' fails -> a non-zero value to 'int errchk'
//(5) free + null 't_concept *info', always do both in this order; prevents leaks
static void	clean_shit_up(t_concept *info)
{
	int errchk;

	if (info)
	{
		if (info->philo)
			kill_philos(info);
		errchk = pthread_mutex_destroy(&info->print);
		if (errchk != 0)
			printf("%s", ERROR_MUTEX_DESTROY);
		free(info);
		info = NULL;
	}
}

/*/--frees and nulls memory allocated to 't_philo *philo' struct(s)--/*/
//(1) loops through n times (n = the number of 't_philo *philo' struct(s)'
//    that were created); this applies the internal code to each of the structs
//(2) uses 'pthread_mutex_unlock()' to unlock the 'p_thread_mutex *l_fork' in 
//    the struct; this needs to be unlocked before it can be destroyed;
//(3) uses 'pthread_mutex_destroy()' to destroy the mutex just unlocked;
//    will return 0 to 'int errchk' on success; cannot use 'fuck_error()' if 
//     wrong because it will fail again;
//(4) frees and nulls t_philo *philo;
static void		kill_philos(t_concept *info)
{
	int i;
	int errchk;

	i = 0;
	while (i < info->no_of_p_f)
	{
		pthread_mutex_unlock(&info->philo[i].l_fork);
		errchk = pthread_mutex_destroy(&info->philo[i].l_fork);
		if (errchk != 0)
			printf("%s", ERROR_MUTEX_DESTROY_FORK);
		i++;
	}
	free(info->philo);
	info->philo = NULL;
}
