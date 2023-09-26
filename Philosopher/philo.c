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

int main(int argc, char **argv)
{
    t_data      *data;
    t_philo     *philo;
    pthread_t   *thread;
    int         x;
    x = 0;

    if (argc > 6 || argc < 5)
        return (0);
    if(!ft_parsing(argv))
        return(print_error());
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
    while (9)
    {
        pthread_mutex_lock(&(philo->data_race));
        if (data->is_dead == 1)
            break;
        pthread_mutex_unlock(&(philo->data_race));
        pthread_mutex_lock(&(philo->data_race));
        if (data->count2_eat == data->num_philo)
        {
            printf("%ldms they all eat %d time\n", start_time(philo->data), philo->data->count2_eat);
            break;
        }
       // pthread_mutex_unlock(&(philo->data_race));
        usleep(30);
    }
    x = 0;
    while (x < data->num_philo)
    {
        pthread_detach(thread[x]);
        x++;
    }
    free(thread);
    return (0);
}

int ft_parsing(char **argv)
{
    int i;
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


int is_number(char *arg)
{
    int i;
    i = 0;

    while(arg[i])
    {
        if(arg[i] >= 48 && arg[i] <= 57)
            i++;
        else
            return(0);  
    }
    return (1);
}

int print_error()
{
    printf("error\n");
    return(1);
}