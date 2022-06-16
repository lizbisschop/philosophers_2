/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat_sleep_think.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 16:57:23 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/06/16 15:27:36 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void    eat(t_philosopher *philo)
{
    better_sleep(philo->time_eat);
    custom_print(philo, "is eating");
    philo->times_eaten++;
    if (pthread_mutex_unlock(&philo->tab->forks[philo->left_fork - 1]) != 0)
        exit_with_error("unlocking left fork failed");
    philo->tab->locked_forks[philo->left_fork - 1] = false;
    if (pthread_mutex_unlock(&philo->tab->forks[philo->right_fork - 1]) != 0)
        exit_with_error("unlocking right fork failed");
    philo->tab->locked_forks[philo->left_fork - 1] = false;   
}

void    grab_forks(t_philosopher *philo)
{
    if (pthread_mutex_lock(&philo->tab->forks[philo->left_fork - 1]) != 0)          
        exit_with_error("locking left fork failed");
    philo->tab->locked_forks[philo->left_fork - 1] = true;
    custom_print(philo, "has taken fork[l]");
    if (pthread_mutex_lock(&philo->tab->forks[philo->right_fork - 1]) != 0)
        exit_with_error("locking right fork failed");
    philo->tab->locked_forks[philo->left_fork - 1] = true;
    custom_print(philo, "has taken fork[r]");
}

void    *eat_sleep_think(void *p)
{
    t_philosopher *philo = p;
    
    if (philo->philo_id % 2 == 0)
        usleep(75);
    while (!(philo->times_eaten != philo->times_to_eat && philo->times_to_eat_bool == true))
    {
        grab_forks(philo);
        eat(philo);
        custom_print(philo, "is sleeping");
        better_sleep(philo->time_sleep);
        custom_print(philo, "is thinking");
    }

    return (0);
}