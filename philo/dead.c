/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dead.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/16 15:38:24 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/26 14:51:48 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

bool	check_dead(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->tab->dead_mutex);
	if (philo->tab->dead_bool == true)
	{
		// printf("left fork %d | right_fork %d| philo id = %d\n", pthread_mutex_trylock(&philo->tab->forks[philo->left_fork]), pthread_mutex_trylock(&philo->tab->forks[philo->right_fork]), philo->philo_id);
		//TODO: don't unlock mutexes that are already unlocked
		pthread_mutex_unlock(&philo->tab->dead_mutex);
		// if (philo->tab->locked_forks[philo->left_fork] == true)
			pthread_mutex_unlock(&philo->tab->forks[philo->left_fork]);
		// if (philo->tab->locked_forks[philo->right_fork] == true)
			pthread_mutex_unlock(&philo->tab->forks[philo->right_fork]);
		return (true);
	}
	pthread_mutex_unlock(&philo->tab->dead_mutex);
	return (false);
}

int	dying_philo(t_data *data, int i)
{
	custom_print(&data->philos[i], "died");
	pthread_mutex_lock(&data->table.dead_mutex);
	data->table.dead_bool = true;
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
			// race condition
			if (data->philos[i].times_to_eat_bool == true
				&& data->philos[i].times_eaten
				>= data->philos[i].times_to_eat)
				return (0);
			pthread_mutex_lock(&data->table.last_eaten);
			if (time - data->philos[i].last_time_eaten
				> data->philos[i].time_die)
			{
				pthread_mutex_unlock(&data->table.last_eaten);
				dying_philo(data, i);
				printf("id of dying philo = %d | time since last eaten = %li | Times eaten = %d\n", data->philos[i].philo_id, time - data->philos[i].last_time_eaten, data->philos[i].times_to_eat);
				return (0);
			}
			pthread_mutex_unlock(&data->table.last_eaten);
			i++;
		}
		usleep(250);
	}
	return (0);
}
