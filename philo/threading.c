/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threading.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 16:16:30 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/06/17 11:10:46 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void destroy(t_data *data)
{
    int i;

    i = 0;
    while (i < data->total_philos)
    {
        if (data->table.locked_forks[i] == true)
            pthread_mutex_unlock(&data->table.forks[i]);
        int ret = pthread_mutex_destroy(&data->table.forks[i]);
        if (ret != 0)
        {
            printf("i = %d | ret = %d\n", i, ret);
            exit_with_error("destroying fork mutex failed");
        }
        i++;
    }
    if (pthread_mutex_destroy(&data->table.write) != 0)
    {
        exit_with_error("destroying write mutex failed");
    }
    if (pthread_mutex_destroy(&data->table.dead_mutex) != 0)
        exit_with_error("destroying dead mutex failed");
}

void join_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->total_philos)
    {
        if (pthread_join(data->table.threads[i], NULL) != 0)
            exit_with_error("pthread join failed");
        i++;
    }
}

void threading(t_data *data)
{
    int i;

    i = 0;
    while (i < data->total_philos)
    {
        if (pthread_create(&(data->table.threads[i]), NULL, eat_sleep_think,
				(void *)&(data->philos[i])) != 0)
            exit_with_error("thread creation failed");
        i++;
    }
    if (pthread_create(&(data->table.dead), NULL, dead, data) != 0)
        exit_with_error("thread creation failed");
    join_threads(data);
    destroy(data);
}