/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 16:03:30 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/25 13:49:42 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	set_philo_info(t_philosopher *philo, int argc, char **argv)
{
	philo->total_philos = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	// philo->last_time_eaten = philo->tab->start_time;
	philo->times_eaten = 0;
	if (philo->time_die < 0 || philo->time_eat < 0
		|| philo->time_sleep < 0 || philo->total_philos < 0)
		return (FAIL);
	if (argc == 6)
	{
		philo->times_to_eat = ft_atoi(argv[5]);
		if (philo->times_to_eat < 0)
			return (FAIL);
		philo->times_to_eat_bool = true;
	}
	else
		philo->times_to_eat_bool = false;
	philo->right_fork = philo->philo_id - 1;
	if (philo->philo_id == 1)
		philo->left_fork = philo->total_philos - 1;
	else
		philo->left_fork = (philo->philo_id - 1) - 1;
	return (0);
}

int	init_philos(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	data->total_philos = ft_atoi(argv[1]);
	data->philos = (t_philosopher *)malloc(sizeof(t_philosopher)
			* data->total_philos);
	if (!data->philos)
		return (handle_error("Malloc failed"));
	// data->start_time = get_time_now();
	while (i < data->total_philos)
	{
		data->philos[i].tab = &data->table;
		data->philos[i].philo_id = i + 1;
		if (set_philo_info(&data->philos[i], argc, argv) == FAIL)
			return (handle_error("Wrong input"));
		i++;
	}
	return (0);
}
