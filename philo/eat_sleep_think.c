/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 16:57:23 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/25 13:53:56 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

bool	eat(t_philosopher *philo)
{
	philo->times_eaten++;
	custom_print(philo, "is eating");
	better_sleep(philo->time_eat);
	pthread_mutex_lock(&philo->tab->last_eaten);
	philo->last_time_eaten = get_time_now();
	pthread_mutex_unlock(&philo->tab->last_eaten);
	if (check_dead(philo) == true)
		return (false);
	philo->tab->locked_forks[philo->left_fork] = false;
	pthread_mutex_unlock(&philo->tab->forks[philo->left_fork]);
	if (check_dead(philo) == true)
		return (false);
	philo->tab->locked_forks[philo->right_fork] = false;
	pthread_mutex_unlock(&philo->tab->forks[philo->right_fork]);
	if (check_dead(philo) == true)
		return (false);
	return (true);
}

bool	grab_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->tab->forks[philo->left_fork]);
	philo->tab->locked_forks[philo->left_fork] = true;
	if (check_dead(philo) == true)
		return (false);
	custom_print(philo, "has taken a fork[l]");
	if (philo->total_philos == 1)
		return (false);
	pthread_mutex_lock(&philo->tab->forks[philo->right_fork]);
	philo->tab->locked_forks[philo->right_fork] = true;
	if (check_dead(philo) == true)
		return (false);
	custom_print(philo, "has taken a fork[r]");
	return (true);
}

void	*eat_sleep_think(void *p)
{
	t_philosopher	*philo;

	philo = p;
	if (philo->philo_id % 2 == 0)
		usleep(75);
	while (!(philo->times_eaten == philo->times_to_eat
			&& philo->times_to_eat_bool == true))
	{
		if (grab_forks(philo) == false)
			break ;
		if (check_dead(philo) == true)
			break ;
		if (eat(philo) == false)
			break ;
		if (check_dead(philo) == true || (philo->times_eaten
				== philo->times_to_eat && philo->times_to_eat_bool == true))
			break ;
		custom_print(philo, "is sleeping");
		better_sleep(philo->time_sleep);
		if (check_dead(philo) == true)
			break ;
		custom_print(philo, "is thinking");
	}
	return (NULL);
}