/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:45:15 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/01 16:25:08 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h> //usleep//
# include <pthread.h>
# include <sys/time.h> //timeval stuct//
# include <stdio.h>

//--definitions of macros for error codes--//
# define ERROR_INPUT_INVALID "Invalid input: please enter 4 valid postitive non-zero integer(s). e.g. 8, 420, 696, +666\n"
# define ERROR_MUTEX_INIT "Error: The forks couldn't be found!"
# define ERROR_TABLE "Error: Table spontaniously combusted and the restaurant had to close down (so all philosophers probably starved to death but who knows really)\n"
# define ERROR_LOCK_MUTEX "Error: One of the philosophers couldn't pick up her fork\n"
# define ERROR_UNLOCK_MUTEX "Error: One of the philosophers wouldn't give up their fork!\n"
# define ERROR_MUTEX_DESTROY "Error: Mutex did not perish and now its ghost lingers...\n"
# define ERROR_MUTEX_DESTROY_FORK "Error: The forks proved indestructable and now you must suffer the consequenes...\n"
# define ERROR_MALLOC "Error: Restaurant was fully book! They couldn't allocate you a table for your philosophers - you should have called ahead you numnut\n"
# define ERROR_THREAD_CREATION "Error: Threads could not be created!\n"
# define ERROR_THREAD_JOIN "Error: Threads could not be joined!\n"
# define ERROR_TIME "Error: I don't how to read a clock so this just isn't going to work, sorry\n"
# define ERROR_USLEEP "Error: Philosophers did not hesitate\n"
# define ERROR_DIED "Error: Philosopher died and the ritual failed :(\n"
# define NOT_ERROR_FULL "not an error just unfinished\n"

//--structure to define a 'philosopher' and all their elements--//
typedef struct	s_philo
{
	int					id;
	pthread_mutex_t		l_fork;
	struct s_philo		*r_philo;
	int					times_eaten;
	long int			time_birth_n_last_eaten;
	long int			time_since_eaten;
	pthread_t			thread;
}						t_philo;

//--structure to encapsulate the concept and hold everything necessary for program to be executed - the master struct if you will--//
typedef struct	s_concept
{
	int					no_of_p_f;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					times_must_eat;
	long int			start_time;
	pthread_mutex_t		print;
	struct s_philo		*philo;
	int					thread_id;
	int					death_status;
}				t_concept;

//--initialise.c--//
void 	initialise(int argc, char **argv, t_concept *info);

//--seat_philos_at_table.c--//
void		seat_philos_at_table(t_concept *info);

//--start_the_feast.c--//
void		start_the_feast(t_concept *info);

//--feasting.c--//
void		*feasting(void *voidptr_info);
/*static void		pick_up_forks(t_philo *philo);
static void		put_down_forks(t_philo *philo);
static void 	nap_time_n_pondering(t_concept*info, t_philo *philo);
static void		check_if_died(t_concept *info, t_philo *philo);*/

//--time.c--//
long int		whats_the_time(t_concept *info);
//long int		elapsed_run_time(t_concept *info);
//static void		hesitate(t_concept *info);
void		do_for_x_time(long int time);
void		custom_usleep(t_concept *info, int time);

//--print.c--//
void		print(t_concept *info, t_philo *philo, int status_msg);
void		print_died(t_concept *info, t_philo *philo);

//--clean.c--//
void		fuck_error(t_concept *info, char *errorcode);

#endif