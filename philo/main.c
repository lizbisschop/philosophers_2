/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 15:23:43 by lbisscho      #+#    #+#                 */
/*   Updated: 2022/06/29 13:28:55 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int exit_with_error(char *str)
{
    printf("%s\n", str);
    exit(0);
}


//TODO: check for error input

int	main(int argc, char **argv)
{
    t_data data;
    
	if (argc != 5 && argc != 6)
        return (exit_with_error("Error: wrong number of arguments"));
    data.start_time = get_time_now();
    init_table(argv, &data);
    init_philos(argc, argv, &data);
    threading(&data);
}
