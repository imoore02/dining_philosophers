/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seat_philos_at_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:25:29 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/10/20 13:45:57 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//--------creating (initiating and mallocing) doubly circular linked list to represent the philosophers at the circular table--------//

#include "philo.h"

void	seat_philos_at_table(t_concept *info)
{
	int i;

	i = 1;
	while(i <= no_of_p_f)
	{
		add_node(info, &info->table_of_philos, i);
		i++;
	}
	if (!info->table_of_philos)
		fuck_error(info, ERROR_TABLE);
}

//--adding the new node to the bottom of the list--//
//notes: something will need to be freed but ideally when the list is cleared (end of program) or when a node is deleted
void	add_node(t_concept *info, t_philo **first, int id)
{
	t_philo *new;
	t_philo *end;
	
	if (*first)
	{
		new = (t_philo *)malloc(sizeof(t_philo));
		if(new == NULL)
			fuck_error(info, ERROR_MALLOC);
		new->r_philo = (*first);
		end->r_philo = new;
		new->id = id;
		new->times_eaten = 0;
		pthread_mutex_init(&info->new->l_fork, NULL);
	}
	else
		(*first) = init_philo(info);
}

//--initiating the head pointer of a stack--//
t_philo *init_philo(t_concept *info, int id)
{
	t_philo *new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if(new == NULL)
		fuck_error(info, ERROR_MALLOC);
	new->r_philo = new;
	new->id = id;
	new->times_eaten = 0;
	pthread_mutex_init(&info->new->l_fork, NULL);
	return (new);
}

//--deletes a node from the top of the list (and sets the r_philonode to be head pointer)--//
void	del_node(t_concept *info, t_philo **sacrifice)
{
	t_philo		*tmp;

	if (*sacrifice)
	{
		if ((*sacrifice)->r_philo == (*sacrifice))
		{
			free(*sacrifice);
			(*sacrifice) = NULL;
			if (*sacrifice)
				fuck_error(info, ERROR_FREE);
		}
		else
		{
			tmp = (*sacrifice);
			(*sacrifice) = (*sacrifice)->r_philo;
			free(tmp);
			tmp = NULL;
			if (tmp)
				fuck_error(info, ERROR_FREE);
		}
	}
}