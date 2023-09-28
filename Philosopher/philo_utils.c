/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:25:00 by marvin            #+#    #+#             */
/*   Updated: 2023/08/27 11:25:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nbr)
{
	int		value;
	int		signe;
	char	*str;

	str = (char *)nbr;
	value = 0;
	signe = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signe = -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		value *= 10;
		value += *str - '0';
		str++;
	}
	return (signe * value);
}

void	ft_print(int para, t_philo *philo)
{
	if (ft_verif_end(philo) == 1)
		;
	else
	{
		pthread_mutex_lock(&(philo->print));
		if (para == 0 && ft_verif_end(philo) == 0)
			printf("%ldms %d has taken a fork\n", start_time(philo->data),
				philo->identity + 1);
		if (para == 1 && ft_verif_end(philo) == 0)
			printf("%ldms %d is eating\n", start_time(philo->data),
				philo->identity + 1);
		if (para == 2 && ft_verif_end(philo) == 0)
			printf("%ldms %d is thinking\n", start_time(philo->data),
				philo->identity + 1);
		if (para == 3 && ft_verif_end(philo) == 0)
			printf("%ldms %d is sleeping\n", start_time(philo->data),
				philo->identity + 1);
		if (para == 4 && ft_verif_end(philo) == 0)
			printf("%ldms %d has died\n", start_time(philo->data),
				philo->identity + 1);
		pthread_mutex_unlock(&(philo->print));
		return ;
	}
}

void	ft_mutex(t_philo *philo)
{
	if (philo->identity % 2 == 0)
	{
		pthread_mutex_lock(&(philo->f[philo->identity]));
		ft_print(0, philo);
		pthread_mutex_lock(&(philo->f[(philo->identity + 1)
				% philo->data->num_philo]));
		ft_print(0, philo);
	}
	else
	{
		pthread_mutex_lock(&(philo->f[(philo->identity + 1)
				% philo->data->num_philo]));
		ft_print(0, philo);
		pthread_mutex_lock(&(philo->f[philo->identity]));
		ft_print(0, philo);
	}
	ft_print(1, philo);
	philo->time_last_eat = current_time() + philo->data->time_e;
	usleep(philo->data->time_e * 1000);
	pthread_mutex_unlock(&(philo->f[philo->identity]));
	pthread_mutex_unlock(&(philo->f[(philo->identity + 1)
			% philo->data->num_philo]));
	pthread_mutex_lock(&(philo->data_race));
	philo->n_meal++;
	pthread_mutex_unlock(&(philo->data_race));
}

int	verif_max_meal(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data_race));
	if (philo->n_meal == philo->data->max_e && philo->data->max_e != -9)
	{
		philo->data->count2_eat += 1;
		if (philo->data->count2_eat == philo->data->num_philo)
		{
			pthread_mutex_unlock(&(philo->data_race));
			return (1);
		}
	}
	pthread_mutex_unlock(&(philo->data_race));
	return (0);
}

int	verif_d_sleep(t_philo *philo)
{
	if (usleep_sleep(philo) == 1 && ft_verif_end(philo) == 0)
	{
		philo->data->is_dead = 1;
		pthread_mutex_lock(&(philo->print));
		printf("%ldms %d has died\n", start_time(philo->data),
			philo->identity + 1);
		return (1);
	}
	return (0);
}
