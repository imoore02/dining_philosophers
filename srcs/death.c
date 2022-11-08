/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:48:27 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/07 21:04:00 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//_______________ CONSTANTLY MONITORS FOR DEATH AMONGST PHILOS________________//
//note: functions appear in the order they are called;

#include "../includes/philo.h"

static void check_if_died(t_concept *info, int *i);

/*/--constantly checks through all philos to see if any have died--/*/
//notes: function called by 'pthread_create()', line 34 (start_the_feast.c);
//(1) have to typecast the void pointer (argument) into type 't_concept *info';
//(2) if input was not given for times_must_eat (how many times a philosopher must eat)
//	  it will call 'check_if_dead()' while it hasnt eaten all the times it needs to
//    and its not dead;
//(3) else it will only check if its not dead - and will call 'check_if_dead()'
//note: 'info->death_status' is altered inside 'check_if_died()';
void	*death(void *voidptr_info)
{
	t_concept *info;
	int i;
	
	info = (t_concept *)voidptr_info;
	i = 0;
	if (info->times_must_eat != 0)
	{
		while (info->philo[i].times_eaten != info->times_must_eat && !info->death_status)
			check_if_died(info, &i);
	}
	else 
	{
		while(!info->death_status)
			check_if_died(info, &i);
	}
	return (0);
}

/*/--checks if a philo has died (if a particular condition is met)--/*/
//(1) checks if the time passed since a philo last ate (the current time - when the philo last ate)
//    is greater than info->time_to_die(how much time can go past without philo starving)
//(2) if this condition is met; it will call 'print_died()', line x (print.c); it will set
//    info->death_status to 1 (meaning that !info->death_status is now untrue so wherever this
//    condition is called it will no longer run); it will call 'fuck_error()', line 25 (clean.c)
//    to exit to program
void check_if_died(t_concept *info, int *i)
{
	if ((whats_the_time(info) - info->philo[*i].time_birth_n_last_eaten) > info->time_to_die)
	{
		print_died(info, info->philo);
		info->death_status = 1;
		fuck_error(info, ERROR_DIED);
	}
}