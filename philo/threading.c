/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threading.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 16:16:30 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/08/03 13:15:27 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	destroy(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->total_philos)
	{
		ret = pthread_mutex_destroy(&data->table.forks[i]);
		if (ret != 0)
			return (handle_error("Error: destroying fork mutex failed"));
		i++;
	}
	if (pthread_mutex_destroy(&data->table.write) != 0)
		return (handle_error("Error: destroying write mutex failed"));
	if (pthread_mutex_destroy(&data->table.dead_mutex) != 0)
		return (handle_error("Error: destroying dead mutex failed"));
	if (pthread_mutex_destroy(&data->table.starting) != 0)
		return (handle_error("Error: destroying starting mutex failed"));
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_join(data->table.threads[i], NULL) != 0)
			return (handle_error("Error: pthread join failed"));
		i++;
	}
	if (pthread_join(data->table.dead, NULL) != 0)
		return (handle_error("Error: pthread join failed"));
	return (0);
}

int	threading(t_data *data)
{
	int	i;

	i = 0;
	data->table.start_time = get_time_now();
	while (i < data->total_philos)
	{
		data->philos[i].last_time_eaten = data->table.start_time;
		i++;
	}
	i = 0;
	pthread_mutex_lock(&data->table.starting);
	while (i < data->total_philos)
	{
		if (pthread_create(&(data->table.threads[i]), NULL, &eat_sleep_think,
				(void *)&(data->philos[i])) != 0)
			return (handle_error("Error: thread creation failed"));
		i++;
	}
	pthread_mutex_unlock(&data->table.starting);
	if (pthread_create(&(data->table.dead), NULL, &dead, data) != 0)
		return (handle_error("Error: thread creation failed"));
	join_threads(data);
	destroy(data);
	return (0);
}
