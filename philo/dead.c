/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dead.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 15:38:24 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/06/17 15:28:12 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

bool check_dead(t_philosopher *philo)
{
    if (pthread_mutex_lock(&philo->tab->dead_mutex))
        exit_with_error("mutex locking failed");
    if (philo->tab->dead_bool == true)
    {

        //TODO: don't unlock mutexes that are already unlocked

        // printf("philo id = %d\n", philo->philo_id);
        // printf(philo->tab->dead_bool ? "true\n" : "false\n");
        if (pthread_mutex_unlock(&philo->tab->dead_mutex) != 0)
            exit_with_error("mutex unlock failed");
        // if (philo->tab->locked_forks[philo->left_fork - 1] == true)
        // {
            if(pthread_mutex_unlock(&philo->tab->forks[philo->left_fork - 1]) != 0)
                exit_with_error("pthread mutex unlock failed");
        // }
        // if (philo->tab->locked_forks[philo->right_fork - 1] == true)
        // {
            if(pthread_mutex_unlock(&philo->tab->forks[philo->right_fork - 1]) != 0)
                exit_with_error("pthread mutex unlock failed");
        // }
        return (true);
    }
    if (pthread_mutex_unlock(&philo->tab->dead_mutex) != 0)
        exit_with_error("mutex unlock failed");
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
            
            if (pthread_mutex_lock(&data->table.last_eaten) != 0)
                exit_with_error("locking last eaten mutex failed");
            if (time - data->philos[i].last_time_eaten > data->philos[i].time_die)
            {
                if (pthread_mutex_lock(&data->table.dead_mutex) != 0)
                    exit_with_error("locking dead mutex failed");
                // printf("id of dying philo = %d | time since last eaten = %li\n", data->philos[i].philo_id, time - data->philos[i].last_time_eaten);
                custom_print(&data->philos[i], "died");
                data->table.dead_bool = true;
                if (pthread_mutex_unlock(&data->table.last_eaten) != 0)
                    exit_with_error("locking last eaten mutex failed");
                if (pthread_mutex_unlock(&data->table.dead_mutex) != 0)
                    exit_with_error("unlocking dead mutex failed");
                return (0);
            }
            if (pthread_mutex_unlock(&data->table.last_eaten) != 0)
                exit_with_error("locking last eaten mutex failed");
        }
    }
    return (0);
}
