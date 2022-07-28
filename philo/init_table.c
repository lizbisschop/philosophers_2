/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_table.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 16:10:44 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/28 14:05:55 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		if (pthread_mutex_init(&data->table.forks[i], NULL) != 0)
			return (handle_error("Error: pthread_mutex_init failed"));
		i++;
	}
	if (pthread_mutex_init(&data->table.write, NULL) != 0)
		return (handle_error("Error: pthread_mutex_init failed"));
	if (pthread_mutex_init(&data->table.dead_mutex, NULL) != 0)
		return (handle_error("Error: pthread_mutex_init failed"));
	if (pthread_mutex_init(&data->table.last_eaten, NULL) != 0)
		return (handle_error("Error: pthread_mutex_init_failed"));
	return (0);
}

int	init_table(char **argv, t_data *data)
{
	int	i;

	i = 0;
	data->total_philos = ft_atoi(argv[1]);
	if (data->total_philos <= 0)
		return (handle_error("Error: Wrong input"));
	data->table.dead_bool = false;
	data->table.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->total_philos);
	data->table.threads = (pthread_t *)malloc(sizeof(pthread_t)
			* data->total_philos);
	data->table.locked_forks = (bool *)malloc(sizeof(bool)
			* data->total_philos);
	if (!data->table.forks || !data->table.threads || !data->table.locked_forks)
		return (handle_error("Error: Malloc failed"));
	while (i < data->total_philos)
	{
		data->table.locked_forks[i] = false;
		i++;
	}
	mutex_init(data);
	return (0);
}
