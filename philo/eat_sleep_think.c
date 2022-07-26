/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 16:57:23 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/26 12:42:49 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

bool	eat(t_philosopher *philo)
{
	philo->times_eaten++;
	if (custom_print(philo, "is eating") == true)
	{
		// printf("eating is going wronggggg with philo %d\n", philo->philo_id);
		return (false);
	}
	pthread_mutex_lock(&philo->tab->last_eaten);
	philo->last_time_eaten = get_time_now();
	pthread_mutex_unlock(&philo->tab->last_eaten);
	better_sleep(philo->time_eat);
	// if (check_dead(philo) == true)
	// 	return (false);
	// philo->tab->locked_forks[philo->left_fork] = false;
	pthread_mutex_unlock(&philo->tab->forks[philo->left_fork]);
	// if (check_dead(philo) == true)
		// return (false);
	// philo->tab->locked_forks[philo->right_fork] = false;
	pthread_mutex_unlock(&philo->tab->forks[philo->right_fork]);
	// if (check_dead(philo) == true)
		// return (false);
	return (true);
}

bool	grab_forks(t_philosopher *philo)
{
	// printf("we are all just waiting to float here %d\n", philo->philo_id);
	pthread_mutex_lock(&philo->tab->forks[philo->left_fork]);
	// printf("we passed the wait list %d\n", philo->philo_id);
	// philo->tab->locked_forks[philo->left_fork] = true;
	// if (check_dead(philo) == true)
	// 	return (false);
	if (custom_print(philo, "has taken a fork[l]") == true)
	{
		// printf("custom print taking fork [l] went wrong\n");
		return (false);
	}
	if (philo->total_philos == 1)
		return (false);
	// printf("we are all just waiting to float here %d\n", philo->philo_id);
	pthread_mutex_lock(&philo->tab->forks[philo->right_fork]);
	// printf("we passed the wait list %d\n", philo->philo_id);
	// philo->tab->locked_forks[philo->right_fork] = true;
	// if (check_dead(philo) == true)
		// return (false);
	if (custom_print(philo, "has taken a fork[r]") == true)
	{
		// printf("custom print taking fork[r] went wrong\n");	
		return (false);
	}
	return (true);
}

void	*eat_sleep_think(void *p)
{
	t_philosopher	*philo;

	philo = p;
	if (philo->philo_id % 2 == 0)
		usleep(200);
	while (!(philo->times_eaten == philo->times_to_eat
			&& philo->times_to_eat_bool == true))
	{
		if (grab_forks(philo) == false)
			break ;
		// if (check_dead(philo) == true)
		// 	break ;
		if (eat(philo) == false)
			break ;
		if ((philo->times_eaten	== philo->times_to_eat
				&& philo->times_to_eat_bool == true))
			break ;
		if (custom_print(philo, "is sleeping") == true)
		{
			// printf("something went wrong with sleeping\n");
			break ;
		}
		better_sleep(philo->time_sleep);
		// if (check_dead(philo) == true)
		// 	break ;
		if (custom_print(philo, "is thinking") == true)
		{
			// printf("something went wrong with thinking\n");
			break ;
		}
		// printf("finish thinking\n");
	}
	// printf("hhhhaaaaallllooooooo\n");
	return (NULL);
}