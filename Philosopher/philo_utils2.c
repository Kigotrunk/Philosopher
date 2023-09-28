/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:05:04 by marvin            #+#    #+#             */
/*   Updated: 2023/09/27 11:05:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_dead(t_philo *philo, long t_last_eat)
{
	if (t_last_eat >= philo->data->time_d && ft_verif_end(philo) == 0)
	{
		pthread_mutex_lock(&(philo->data_race));
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&(philo->data_race));
		pthread_mutex_lock(&(philo->print));
		printf("%ldms %d has died\n", start_time(philo->data),
			philo->identity + 1);
		return (1);
	}
	return (0);
}
