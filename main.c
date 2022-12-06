/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:58:28 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/28 12:59:24 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	int		fd;
	t_game	*so_long;

	if (argc != 2)
		return (put_error("Invalid number of arguments"));
	if (check_map(argv[1]) == -1)
		return (-1);
	so_long = (t_game *)malloc(sizeof(t_game));
	if (!so_long)
		return (put_error("Memory problem"));
	fd = open(argv[1], O_RDONLY);
	so_long->map = get_map(fd);
	close(fd);
	if (!so_long->map)
		return (free_so_long(so_long));
	ft_putstr_fd("Starting game...\n", 1);
	start_game(so_long);
	free_so_long(so_long);
	return (0);
}
