/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_table.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 16:10:44 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/06/17 10:21:46 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void mutex_init(t_data *data)
{
    int i;

    i = 0;
    while (i < data->total_philos)
    {
        if (pthread_mutex_init(&data->table.forks[i], NULL) != 0)
            exit_with_error("pthread_mutex_init failed");
        i++;
        
    }
    if (pthread_mutex_init(&data->table.write, NULL) != 0)
        exit_with_error("pthread_mutex_init failed");
    if (pthread_mutex_init(&data->table.dead_mutex, NULL) != 0)
        exit_with_error("pthread_mutex_init failed");
}

void init_table(char **argv, t_data *data)
{
    int i;

    i = 0;
    data->total_philos = ft_atoi(argv[1]);
    data->table.dead_bool = false;
    data->table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->total_philos + 1);
    data->table.threads = (pthread_t *)malloc(sizeof(pthread_t) * data->total_philos + 1);
    data->table.locked_forks = (bool *)malloc(sizeof(bool) * data->total_philos + 1);
    while (i < data->total_philos)
    {
        data->table.locked_forks[i] = false;
        i++;
    }
    data->table.start_time = get_time_now();
    mutex_init(data); 
}
