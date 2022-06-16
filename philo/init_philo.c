/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 16:03:30 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/06/16 15:16:53 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void set_philo_info(t_philosopher *philo, int argc, char **argv)
{
    philo->dead = false;
    philo->total_philos = ft_atoi(argv[1]);
    philo->time_die = ft_atoi(argv[2]);
    philo->time_eat = ft_atoi(argv[3]);
    philo->time_sleep = ft_atoi(argv[4]);
    //if times to eat is defined
    if (argc == 6)
    {
        philo->times_to_eat = ft_atoi(argv[5]);
        philo->times_to_eat_bool = true;
    }
    else
        philo->times_to_eat_bool = false;
    philo->right_fork = philo->philo_id;
    if (philo->philo_id == 1)
        philo->left_fork = philo->total_philos;
    else
        philo->left_fork = philo->philo_id - 1;
}

void init_philos(int argc, char **argv, t_data *data)
{
    int i;

    i = 0;
    data->total_philos = ft_atoi(argv[1]);
    data->philos = (t_philosopher *)malloc(sizeof(t_philosopher) * data->total_philos + 1);
    while (i < data->total_philos)
    {
        data->philos[i].tab = &data->table;
        data->philos[i].philo_id = i + 1;
        set_philo_info(&data->philos[i], argc, argv);
        printf("philo id = %d | time_die = %d | time_eat = %d | time_sleep = %d | left_fork = %d | right_fork = %d\n", data->philos[i].philo_id, data->philos[i].time_die, data->philos[i].time_eat, data->philos[i].time_sleep, data->philos[i].left_fork, data->philos[i].right_fork);
        i++;
    }
}
