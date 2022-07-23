/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threading.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 16:16:30 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/23 16:09:17 by lbisscho      ########   odam.nl         */
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
		if (data->table.locked_forks[i] == true)
			pthread_mutex_unlock(&data->table.forks[i]);
		ret = pthread_mutex_destroy(&data->table.forks[i]);
		if (ret != 0)
			return (handle_error("destroying fork mutex failed"));
		i++;
	}
	if (pthread_mutex_destroy(&data->table.write) != 0)
		return (handle_error("destroying write mutex failed"));
	if (pthread_mutex_destroy(&data->table.dead_mutex) != 0)
		return (handle_error("destroying dead mutex failed"));
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_join(data->table.threads[i], NULL) != 0)
			return (handle_error("pthread join failed"));
		i++;
	}
	if (pthread_join(data->table.dead, NULL) != 0)
		return (handle_error("pthread join failed"));
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
		if (pthread_create(&(data->table.threads[i]), NULL, &eat_sleep_think,
				(void *)&(data->philos[i])) != 0)
			return (handle_error("thread creation failed"));
		i++;
	}
	if (pthread_create(&(data->table.dead), NULL, &dead, data) != 0)
		return (handle_error("thread creation failed"));
	join_threads(data);
	destroy(data);
	return (0);
}
