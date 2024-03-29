/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 15:23:43 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/08/03 12:06:39 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	handle_error(char *str)
{
	printf("%s\n", str);
	return (FAIL);
}

void	free_stuff(t_data *data)
{
	int	i;

	i = 0;
	if (data->table.locked_forks)
		free(data->table.locked_forks);
	if (data->table.forks)
		free(data->table.forks);
	if (data->table.threads)
		free(data->table.threads);
	if (data->philos)
		free(data->philos);
	(void)data;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (handle_error("Error: wrong number of arguments"));
	if (init_table(argv, &data) == FAIL)
	{
		free_stuff(&data);
		return (0);
	}
	if (init_philos(argc, argv, &data) == FAIL)
	{
		free_stuff(&data);
		return (0);
	}
	if (threading(&data) == FAIL)
	{
		free_stuff(&data);
		return (0);
	}
	free_stuff(&data);
	return (0);
}
