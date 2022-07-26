/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 16:57:23 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/26 14:51:25 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

bool	eat(t_philosopher *philo)
{
	philo->times_eaten++;
	if (custom_print(philo, "is eating") == true)
		return (false);
	pthread_mutex_lock(&philo->tab->last_eaten);
	philo->last_time_eaten = get_time_now();
	pthread_mutex_unlock(&philo->tab->last_eaten);
	better_sleep(philo->time_eat);
	pthread_mutex_unlock(&philo->tab->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->tab->forks[philo->right_fork]);
	return (true);
}

bool	grab_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->tab->forks[philo->left_fork]);
	if (custom_print(philo, "has taken a fork[l]") == true)
		return (false);
	if (philo->total_philos == 1)
		return (false);
	pthread_mutex_lock(&philo->tab->forks[philo->right_fork]);
	if (custom_print(philo, "has taken a fork[r]") == true)
		return (false);
	return (true);
}

void	*eat_sleep_think(void *p)
{
	t_philosopher	*philo;

	philo = p;
	if (philo->philo_id % 2 == 0)
		usleep(500);
	while (!(philo->times_eaten == philo->times_to_eat
			&& philo->times_to_eat_bool == true))
	{
		if (grab_forks(philo) == false)
			break ;
		if (eat(philo) == false)
			break ;
		if ((philo->times_eaten	== philo->times_to_eat
				&& philo->times_to_eat_bool == true))
			break ;
		if (custom_print(philo, "is sleeping") == true)
			break ;
		better_sleep(philo->time_sleep);

		if (custom_print(philo, "is thinking") == true)
			break ;
	}
	return (NULL);
}