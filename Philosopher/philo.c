/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 19:20:26 by marvin            #+#    #+#             */
/*   Updated: 2023/08/02 19:20:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		*data;
	t_philo		*philo;
	pthread_t	*thread;
	int			x;

	x = 0;
	if (argc > 6 || argc < 5)
		return (0);
	if (!ft_parsing(argv))
		return (print_error());
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (init_data(data, argv, argc))
		return (0);
	philo = malloc(sizeof(t_philo) * data->num_philo);
	thread = malloc(sizeof(pthread_t) * data->num_philo);
	if (!philo || !thread)
		return (1);
	if (init_philo(data, philo))
		return (1);
	if (!main_part(philo, data, x, thread))
		return (0);
}

int	ft_parsing(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_number(argv[i]))
			return (0);
		else
			i++;
	}
	return (1);
}

int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] >= 48 && arg[i] <= 57)
			i++;
		else
			return (0);
	}
	return (1);
}

int	print_error(void)
{
	printf("error\n");
	return (1);
}

int	ft_verif_end(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data_race));
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&(philo->data_race));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data_race));
	usleep(25);
	pthread_mutex_lock(&(philo->data_race));
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&(philo->data_race));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data_race));
	return (0);
}
