/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dead.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 15:38:24 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/22 15:26:11 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

bool check_dead(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->tab->dead_mutex);
    if (philo->tab->dead_bool == true)
    {

        //TODO: don't unlock mutexes that are already unlocked

        // printf("philo id = %d\n", philo->philo_id);
        // printf(philo->tab->dead_bool ? "true\n" : "false\n");
        pthread_mutex_unlock(&philo->tab->dead_mutex);
        // if (philo->tab->locked_forks[philo->left_fork - 1] == true)
        // {
            pthread_mutex_unlock(&philo->tab->forks[philo->left_fork - 1]);
        // }
        // if (philo->tab->locked_forks[philo->right_fork - 1] == true)
        // {
            pthread_mutex_unlock(&philo->tab->forks[philo->right_fork - 1]);
        // }
        return (true);
    }
    pthread_mutex_unlock(&philo->tab->dead_mutex);
    return (false);
}

void *dead(void* d)
{
    int i;
    t_data *data;

    i = 0;
    data = d;
    while (true)
    {
        while (i < data->total_philos)
        {
            long time;
            
            time = get_time_now();
            
            pthread_mutex_lock(&data->table.last_eaten);
            if (time - data->philos[i].last_time_eaten > data->philos[i].time_die)
            {
                if (data->philos[i].times_to_eat_bool == true && data->philos[i].times_eaten == data->philos[i].times_to_eat)
                {
                    pthread_mutex_unlock(&data->table.last_eaten);
                    return (0);
                }
                pthread_mutex_lock(&data->table.dead_mutex);
                printf("id of dying philo = %d | time since last eaten = %li | Times eaten = %d\n", data->philos[i].philo_id, time - data->philos[i].last_time_eaten, data->philos[i].times_to_eat);
                custom_print(&data->philos[i], "died");
                data->table.dead_bool = true;
                pthread_mutex_unlock(&data->table.last_eaten);
                pthread_mutex_unlock(&data->table.dead_mutex);
                return (0);
            }
            pthread_mutex_unlock(&data->table.last_eaten);
        }
    }
    return (0);
}
