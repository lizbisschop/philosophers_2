/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dead.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 15:38:24 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/28 13:34:53 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

bool	check_dead(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->tab->dead_mutex);
	if (philo->tab->dead_bool == true)
	{
		pthread_mutex_unlock(&philo->tab->dead_mutex);
		pthread_mutex_unlock(&philo->tab->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->tab->forks[philo->right_fork]);
		return (true);
	}
	pthread_mutex_unlock(&philo->tab->dead_mutex);
	return (false);
}

int	dying_philo(t_data *data, int i)
{
	pthread_mutex_lock(&data->table.dead_mutex);
	custom_print(&data->philos[i], "died");
	data->table.dead_bool = true;
	pthread_mutex_unlock(&data->table.dead_mutex);
	return (0);
}

bool	might_be_dying(t_data *data, int *done_eating)
{
	int	i;

	i = 0;
	while (i < data->total_philos)
	{
		pthread_mutex_lock(&data->table.last_eaten);
		if (data->philos[i].times_to_eat_bool == true
			&& data->philos[i].times_eaten
			>= data->philos[i].times_to_eat)
		{
			(*done_eating)++;
			pthread_mutex_unlock(&data->table.last_eaten);
		}
		if (get_time_now() - data->philos[i].last_time_eaten
			> data->philos[i].time_die)
		{
			pthread_mutex_unlock(&data->table.last_eaten);
			dying_philo(data, i);
			return (true);
		}
		pthread_mutex_unlock(&data->table.last_eaten);
		i++;
	}
	return (false);
}

void	*dead(void *d)
{
	t_data	*data;
	int		done_eating;

	data = d;
	while (true)
	{
		done_eating = 0;
		if (might_be_dying(data, &done_eating) == true)
			return (0);
		if (done_eating == data->total_philos)
			return (0);
		usleep(250);
	}
	return (0);
}
