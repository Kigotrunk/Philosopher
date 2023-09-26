/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:48:50 by marvin            #+#    #+#             */
/*   Updated: 2023/08/23 14:48:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
    int num_philo;
    int time_d;
    int time_e;
    int time_s;
    int count_e;
    int max_e;
    int is_dead;
    int count2_eat;
    time_t start_time;
}  t_data;

typedef struct s_philo
{
    t_data          *data;
    int             identity;
    int             n_meal;
    pthread_mutex_t *f;
    pthread_mutex_t print;
    pthread_mutex_t data_race;
    time_t          time_last_eat;
}   t_philo;

int     ft_parsing(char **argv);
int     is_number(char *arg);
int     ft_atoi(const char *nbr);
int     init_data(t_data *data, char **argv, int argc);
int     verif_data(t_data *data);
void     init_data_philo(t_data *data, t_philo *philo, pthread_mutex_t *fork, pthread_mutex_t print);
int     init_philo(t_data *data, t_philo *philo);
void    *ft_routine(void *arg);
long    current_time(void);
int     check_limits(t_philo *philosopher);
int     print_error();
long    start_time(t_data *data);
int     usleep_sleep(t_philo *philo);
void	ft_print(int para, t_philo *philo);
void	ft_mutex(t_philo *philo);
int	    verif_max_meal(t_philo *philo);
int	    verif_d_sleep(t_philo *philo);
void    *ft_solo(void *arg);
int     ft_verif_end(t_philo *philo);

#endif