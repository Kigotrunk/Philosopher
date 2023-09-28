/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:33:17 by marvin            #+#    #+#             */
/*   Updated: 2023/09/28 11:33:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	infinite_boucle(t_philo *philo, t_data *data, int x)
{
	while (9)
	{
		x = 0;
		while (x < data->num_philo)
		{
			if (current_time() - philo[x].time_last_eat >= data->time_d)
			{
				data->is_dead = 1;
				pthread_mutex_lock(&(philo[x].print));
				printf("%ldms %d has died\n", start_time(philo->data),
					philo[x].identity + 1);
				pthread_mutex_unlock(&(philo[x].print));
				return (1);
			}
			x++;
		}
		if (part_of_infinite(philo, data))
			return (1);
	}
}

int	part_of_infinite(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&(philo->data_race));
	if (data->is_dead == 1)
		return (1);
	pthread_mutex_unlock(&(philo->data_race));
	pthread_mutex_lock(&(philo->data_race));
	if (data->count2_eat == data->num_philo)
	{
		printf("%ldms they all eat %d time\n", start_time(philo->data),
			philo->data->max_e);
		return (1);
	}
	pthread_mutex_unlock(&(philo->data_race));
	usleep(30);
	return (0);
}

int	main_part(t_philo *philo, t_data *data, int x, pthread_t *thread)
{
	if (data->num_philo == 1)
		pthread_create(&thread[0], NULL, ft_solo, philo);
	else
	{
		while (data->num_philo > x)
		{
			pthread_create(&thread[x], NULL, ft_routine, philo + x);
			usleep(30);
			x++;
		}
	}
	while (!infinite_boucle(philo, data, x))
		;
	x = 0;
	while (x < data->num_philo)
	{
		pthread_detach(thread[x]);
		x++;
	}
	return (0);
}
