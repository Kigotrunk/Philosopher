/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 22:13:00 by marvin            #+#    #+#             */
/*   Updated: 2023/09/06 22:13:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long current_time(void) 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long    start_time(t_data *data)
{
    return (current_time() - data->start_time);
}

void    *ft_routine(void *arg)
{
    t_philo *philo;
    long    t_last_eat;

    philo = (t_philo *)arg;
    pthread_mutex_lock(&(philo->data_race));
    if (philo->identity % 2 == 1)
        usleep(30);
    pthread_mutex_unlock(&(philo->data_race));
    while (1)
    {
        ft_mutex(philo);
        if (verif_max_meal(philo))
            return (NULL);
        t_last_eat = current_time() - philo->time_last_eat;
        if (t_last_eat >= philo->data->time_d)
        {
            ft_print(4, philo);
            pthread_mutex_lock(&(philo->data_race));
            philo->data->is_dead = 1;
            pthread_mutex_unlock(&(philo->data_race));
            return (NULL);
        }
        ft_print(2, philo);
        ft_print(3, philo);
        if (verif_d_sleep(philo))
            return (NULL);
    }
    return (NULL);
}

int usleep_sleep(t_philo *philo)
{
    long t_last_eat;
    long time_to_death;
    long time_to_sleep;

    t_last_eat = current_time() - philo->time_last_eat;
    if (t_last_eat >= philo->data->time_d)
        return (1);
    else
    {
        time_to_sleep = philo->data->time_s - t_last_eat;
        if (time_to_sleep > 0)
        {
            if (t_last_eat + time_to_sleep >= philo->data->time_d)
            {
                time_to_death = philo->data->time_d - t_last_eat;
                usleep(time_to_death * 1000);
                return (1);
            }
            else
                usleep(time_to_sleep * 1000);
        }
    }
    return (0);
}

void    *ft_solo(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    usleep(philo->data->time_d * 1000);
    pthread_mutex_lock(&(philo->print));
    printf("%dms 1 has died\n", philo->data->time_d);
    pthread_mutex_unlock(&(philo->print));
    pthread_mutex_lock(&(philo->data_race));
    philo->data->is_dead = 1;
    pthread_mutex_unlock(&(philo->data_race));
    return NULL;
}