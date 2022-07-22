/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 15:23:43 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/07/22 14:03:06 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int exit_with_error(t_philosopher *philo, char *str)
{
    printf("%s\n", str);
    return (0);
    (void)philo;
    // exit(0);
}

void free_stuff(t_data *data)
{
    int i;

    i = 0;
    

    if (data->table.locked_forks)
        free(data->table.locked_forks);
    if (data->table.forks)
        free(data->table.forks);
    if (data->table.threads)
        free(data->table.threads);  
    if (data->philos)
        free(data->philos);
}

int main_function(int argc, char **argv)
{
    t_data data;
    
	if (argc != 5 && argc != 6)
        return (exit_with_error(&data.philos[0], "Error: wrong number of arguments")); // this will segfault
    data.start_time = get_time_now();
    init_table(argv, &data);
    init_philos(argc, argv, &data);
    threading(&data);
    free_stuff(&data);
    return (0);
}

//TODO: check for error input

int	main(int argc, char **argv)
{
    main_function(argc, argv);
    // system("leaks philo");
}
