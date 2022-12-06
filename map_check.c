/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:23:52 by ngalzand          #+#    #+#             */
/*   Updated: 2022/12/05 17:39:55 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_path(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 5 || path[len -1] != 'r' || path[len - 2] != 'e'
		|| path[len - 3] != 'b' || path[len - 4] != '.')
		return (-1);
	return (0);
}

static int	check_wall_and_elements(char **map, unsigned int **elements)
{
	long int		i;
	long int		j;

	i = -1;
	while (map[++i] && i < tablen(map))
	{
		j = -1;
		if (i > 0 && ft_strlen_sl(map[i - 1]) != ft_strlen_sl(map[i]))
			return (put_error("Map is not rectangular"));
		while (++j < (long int)ft_strlen_sl(map[i]))
		{
			if ((i == 0 && map[i][j] != '1')
				|| (i == tablen(map) - 1 && map[i][j] != '1')
				|| (j == 0 && map[i][j] != '1')
				|| ((size_t)j == ft_strlen_sl(map[i]) - 1 && map[i][j] != '1'))
				return (put_error("Map is not surrounded by wall"));
			else if (map[i][j] == 'C' || map[i][j] == 'E' || map[i][j] == 'P')
				check_elem(map[i][j], elements);
			else if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C'
			&& map[i][j] != 'E' && map[i][j] != 'P' && map[i][j] != 'V')
				return (put_error("Map contain invalid character"));
		}
	}
	return (0);
}

static void	flood_fill(char **map, size_t x, size_t y, unsigned int **f_elems)
{
	if (!map[y][x] || map[y][x] == '1' || map[y][x] == 'V')
		return ;
	if (map[y][x] == 'C')
		f_elems[0][0] += 1;
	if (map[y][x] == 'E')
		f_elems[0][1] += 1;
	if (map[y][x] == 'P')
		f_elems[0][2] += 1;
	map[y][x] = '1';
	flood_fill(map, x + 1, y, f_elems);
	flood_fill(map, x - 1, y, f_elems);
	flood_fill(map, x, y + 1, f_elems);
	flood_fill(map, x, y - 1, f_elems);
}

static int	map_isplayable(char **map)
{
	unsigned int	*elements;
	unsigned int	*found_elements;
	t_pos			spawnpos;

	elements = (unsigned int *)ft_calloc(3, sizeof(unsigned int));
	if (!elements)
		return (-1);
	if (check_wall_and_elements(map, &elements) == -1)
		return (-1);
	if (elements[0] == 0 || elements[1] != 1 || elements[2] != 1)
		return (free_and_return(elements, 0, 0,
				"Invalid number of Collectible, Exit or Spawn"));
	found_elements = (unsigned int *)ft_calloc(3, sizeof(unsigned int));
	if (!found_elements)
		free_and_return(elements, 0, 0, "");
	spawnpos = getpos(map, 'P');
	if (spawnpos.x == 0 && spawnpos.y == 0)
		return (free_and_return(elements, found_elements, 0,
				"Can't find path to certain element"));
	flood_fill(map, spawnpos.x, spawnpos.y, &found_elements);
	if (elements[0] != found_elements[0] || elements[1] != found_elements[1]
		|| elements[2] != found_elements[2])
		return (free_and_return(elements, found_elements, 0,
				"Can't find path to certain element"));
	return (free_and_return(elements, found_elements, 0, 0));
}

int	check_map(char *path)
{
	int		fd;
	char	**map;

	ft_putstr_fd("Checking map...\n", 1);
	if (check_path(path) == -1)
		return (put_error("Wrong type for map file"));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (put_error("Can't open map file"));
	map = get_map(fd);
	close(fd);
	if (!map)
		return (put_error("Map initializing error"));
	if (map_isplayable(map) == -1)
	{
		freestrtab(map, tablen(map));
		return (put_error("Error during map verification"));
	}
	freestrtab(map, tablen(map));
	ft_putstr_fd("Check Done.\n", 1);
	return (0);
}
