/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:57:01 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/08 11:36:14 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//__________INITIALISATION: DECLARATIONS, MALLOC, DEFINING VARIABLES_________//
//note: functions appear in the order they are called;

#include "../includes/philo.h"

//---altered ft_atoi does converts char *argv and turns in into an int---//
//notes: deals with (some of the) error checking; checks if only valid digit 
//       characters (including - or +(but only once right before the digit
//       & checks if it is an integer type
static int	atoi_philo(t_concept *info, const char *str)
{
	int	i;
	long long res;

	res = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			fuck_error(info, ERROR_INPUT_INVALID);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	if (((!(str[i] >= '0' && str[i] <= '9')) && str[i] != '\0') || res > 2147483647 || res < -2147483648)
		fuck_error(info, ERROR_INPUT_INVALID);
	return (res);
}


/*/--initialises data structures--/*/
//(1) uses atoi_philo to transform char string inputs (whilst error checking) to their coencidig t_concept *info value;
//(2) sets the info->start_time using 'whats_the_time' function;
//(3) initiates the print mutex which is shared/needs to be access inside all threads;
//(4) 'seat_philos_at_table' will memory allocate and initialise for the philo structs;
void initialise(int argc, char **argv, t_concept *info)
{
	int errchk;

	errchk = pthread_mutex_init(&info->print, NULL);
	if (errchk != 0)
		fuck_error(info, ERROR_MUTEX_INIT);
	info->no_of_p_f = atoi_philo(info, argv[1]);
	info->time_to_die = atoi_philo(info, argv[2]);
	info->time_to_eat = atoi_philo(info, argv[3]);
	info->time_to_sleep = atoi_philo(info, argv[4]);
	info->times_must_eat = -1;
	if (argc == 6)
		info->times_must_eat = atoi_philo(info, argv[5]);
	if (info->no_of_p_f == 0 || info->time_to_die == 0 || info->time_to_eat == 0
			||info->time_to_sleep == 0)
			fuck_error(info, ERROR_INPUT_INVALID);
	info->start_time = whats_the_time(info);
	info->death_status = 0;
	seat_philos_at_table(info);
}