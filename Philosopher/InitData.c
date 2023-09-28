/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitData.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:37:33 by marvin            #+#    #+#             */
/*   Updated: 2023/08/24 11:37:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verif_data(t_data *data)
{
	if (data->time_s <= 0 || data->time_d <= 0 || data->time_s <= 0
		|| data->num_philo <= 0)
		return (1);
	return (0);
}

int	init_data(t_data *data, char **argv, int argc)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_d = ft_atoi(argv[2]);
	data->time_e = ft_atoi(argv[3]);
	data->time_s = ft_atoi(argv[4]);
	data->is_dead = 0;
	if (argc == 6)
		data->max_e = ft_atoi(argv[5]);
	else
		data->max_e = -9;
	if (verif_data(data))
		return (1);
	return (0);
}

int	init_philo(t_data *data, t_philo *philo)
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	int				x;

	x = 0;
	fork = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!fork)
		return (1);
	while (data->num_philo > x)
	{
		pthread_mutex_init(&fork[x], NULL);
		x++;
	}
	pthread_mutex_init(&print, NULL);
	pthread_mutex_init(&philo->data_race, NULL);
	init_data_philo(data, philo, fork, print);
	return (0);
}

void	init_data_philo(t_data *data, t_philo *philo, pthread_mutex_t *fork,
	pthread_mutex_t print)
{
	int	x;

	x = 0;
	while (data->num_philo > x)
	{
		philo[x].identity = x;
		philo[x].f = fork;
		philo[x].print = print;
		philo[x].data = data;
		philo[x].n_meal = 0;
		philo[x].time_last_eat = current_time();
		x++;
	}
	philo->data->start_time = current_time();
}
