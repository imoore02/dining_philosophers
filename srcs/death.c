/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isobelmoore <isobelmoore@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:48:27 by isobelmoore       #+#    #+#             */
/*   Updated: 2022/11/02 14:00:30 by isobelmoore      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_if_died(t_concept *info, t_philo *philo)
{
	if (philo->time_since_eaten > info->time_to_die)
	{
		//print_died(info, philo);
		printf("philo died!");
		fuck_error(info, ERROR_DIED);
		info->death_status = 1;
	}
}