/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dead.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 15:38:24 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/25 13:31:42 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

bool	check_dead(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->tab->dead_mutex);
	if (philo->tab->dead_bool == true)
	{
		//TODO: don't unlock mutexes that are already unlocked
		pthread_mutex_unlock(&philo->tab->dead_mutex);
		if (philo->tab->locked_forks[philo->left_fork] == true)
			pthread_mutex_unlock(&philo->tab->forks[philo->left_fork]);
		if (philo->tab->locked_forks[philo->right_fork] == true)
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
	pthread_mutex_unlock(&data->table.last_eaten);
	pthread_mutex_unlock(&data->table.dead_mutex);
	return (0);
}

void	*dead(void *d)
{
	int		i;
	t_data	*data;
	long	time;

	data = d;
	while (true)
	{
		i = 0;
		while (i < data->total_philos)
		{
			time = get_time_now();
			pthread_mutex_lock(&data->table.last_eaten);
			if (data->philos[i].times_to_eat_bool == true
				&& data->philos[i].times_eaten
				>= data->philos[i].times_to_eat)
			{
				pthread_mutex_unlock(&data->table.last_eaten);
				return (0);
			}
			if (time - data->philos[i].last_time_eaten
				> data->philos[i].time_die)
			{
				dying_philo(data, i);
				printf("id of dying philo = %d | time since last eaten = %li | Times eaten = %d\n", data->philos[i].philo_id, time - data->philos[i].last_time_eaten, data->philos[i].times_to_eat);
				pthread_mutex_unlock(&data->table.last_eaten);
				return (0);
			}
			pthread_mutex_unlock(&data->table.last_eaten);
			i++;
		}
		// usleep(75);
	}
	return (0);
}
