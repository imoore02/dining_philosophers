/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seat_philos_at_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:25:29 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/08 13:18:27 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//_____CREATING (INIT + MALLOC) CIRCULAR LINKED LIST (ALL PIHLOS (TABLE))_____//
//note: functions appear in the order they are called;

#include "../includes/philo.h"

static void		set_values(t_concept *info);
static char		*set_colours(int n);

/*/--mallocs and intialises a metaphorical table of philosophers (i.e a circular
//   linked list containing all the philosophers--/*/
//note: this all happens before any of the threads are created;
//(1) need to malloc the 'size of t_philo' n times (the input for how many
//    philos there are going to be (info->no_of_p_f)); if fails, returns NULL;
//(2) while (i < no_of_p_f) -> means create n philos; for each 'set_values()';
void	seat_philos_at_table(t_concept *info)
{
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->no_of_p_f);
	if (!info->philo)
		fuck_error(info, ERROR_MALLOC);
	set_values(info);
}

/*/--defines all the variables in a philo struct, for each of n philos--/*/
//(1) runs a loop to execute the process n times (n is the no of philos);
//(2) sets the pointers to philo on the right (r_philo) to create a 
//    circular linked list; for each philo except the 'last one' its right philo 
//    will be the one with the id one greater than its; but for the 'last' one (the 
//    one with teh greatest id number), its right philosopher will be the 'first'
//    philo (id = 0);
//(3) philo ids start at 0;
//(4) times_eaten is initialised as 0, as no philosophers have eaten yet;
//(5) 'set_colours()' is called to assign a particular char *string that denotes a
//     colour (to print their message in) for each philo;
//(6) iniate the mutex associated w each philo ('pthead_mutex l_fork'); will return
//    0 to errchk on success;
static void		set_values(t_concept *info)
{
	int errchk;
	int i;
	char *colour;

	i = 0;
	while (i < info->no_of_p_f)
	{
		if (info->no_of_p_f - 1 == i)
			info->philo[i].r_philo = &info->philo[0];
		else
			info->philo[i].r_philo = &info->philo[i + 1];
		info->philo[i].id = i + 1;
		info->philo[i].times_eaten = 0;
		colour = set_colours(i + 1);
		info->philo[i].colour = colour;
		info->philo[i].info = info;
		errchk = pthread_mutex_init(&info->philo[i].l_fork, NULL);
		if (errchk != 0)
			fuck_error(info, ERROR_MUTEX_INIT);
		i++;
	}
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