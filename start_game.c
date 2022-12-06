/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:34:48 by ngalzand          #+#    #+#             */
/*   Updated: 2022/12/05 17:34:50 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	randomtexture(size_t x, size_t y, size_t max)
{
	return (((x % 7 == 0 && y % 7 == 0) + (x * y)) % (max + 1));
}

static void	draw_sidewall(t_game *sl, size_t x, size_t y)
{
	if (x == 0)
		mlx_image_to_window(sl->mlx, sl->wall[3], x * 64, y * 64);
	else if (x == ft_strlen(sl->map[0]) - 1)
		mlx_image_to_window(sl->mlx, sl->wall[4], x * 64, y * 64);
	else if (y == 0)
		mlx_image_to_window(sl->mlx, sl->wall[5], x * 64, y * 64);
	else if (y == (size_t)tablen(sl->map) - 1)
		mlx_image_to_window(sl->mlx, sl->wall[0], x * 64, y * 64);
}

static void	draw_wall(t_game *sl)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (sl->map[y])
	{
		x = 0;
		while (sl->map[y][x])
		{
			if (y == 0 && x == 0)
				mlx_image_to_window(sl->mlx, sl->wall[6], x * 64, y * 64);
			else if (y == 0 && x == ft_strlen(sl->map[0]) - 1)
				mlx_image_to_window(sl->mlx, sl->wall[7], x * 64, y * 64);
			else if (y == (size_t)tablen(sl->map) - 1 && x == 0)
				mlx_image_to_window(sl->mlx, sl->wall[1], x * 64, y * 64);
			else if (y == (size_t)tablen(sl->map) - 1
				&& x == ft_strlen(sl->map[0]) - 1)
				mlx_image_to_window(sl->mlx, sl->wall[2], x * 64, y * 64);
			else
				draw_sidewall(sl, x, y);
			x++;
		}
		y++;
	}
}

static int	draw_map(t_game *sl)
{
	long int	x;
	long int	y;

	draw_wall(sl);
	y = 0;
	while ((size_t)++y < (size_t)tablen(sl->map) - 1)
	{
		x = 0;
		while ((size_t)++x < ft_strlen(sl->map[0]) - 1)
		{
			if (sl->map[y][x] == '0' || sl->map[y][x] == 'C'
			|| sl->map[y][x] == 'E' || sl->map[y][x] == 'P')
				mlx_image_to_window(sl->mlx, sl->grass, x * 64, y * 64);
			if (sl->map[y][x] == 'C')
				mlx_image_to_window(sl->mlx, sl->food[randomtexture(x, y, 1)],
					x * 64, y * 64);
			else if (sl->map[y][x] == '1')
				mlx_image_to_window(sl->mlx, sl->bush[randomtexture(x, y, 1)],
					x * 64, y * 64);
			else if (sl->map[y][x] == 'V')
				mlx_image_to_window(sl->mlx, sl->fireplace, x * 64, y * 64);
		}
	}
	return (0);
}

int	start_game(t_game *so_long)
{
	so_long->mlx = mlx_init(((int32_t)ft_strlen(so_long->map[0])) * 64,
			((int32_t)tablen(so_long->map)) * 64, "so_long", false);
	if (!so_long->mlx)
		return (put_error("Display failed"));
	if (load_assets(so_long) == -1)
		return (-1);
	draw_map(so_long);
	so_long->step = 0;
	food_and_villain_count(so_long);
	so_long->stepstring = mlx_put_string(so_long->mlx, "Steps: 0", 60, 40);
	so_long->nestpos = getpos(so_long->map, 'E');
	so_long->playerpos = getpos(so_long->map, 'P');
	mlx_image_to_window(so_long->mlx, so_long->bird,
		so_long->playerpos.x * 64, so_long->playerpos.y * 64);
	mlx_key_hook(so_long->mlx, &game, so_long);
	mlx_loop_hook(so_long->mlx, &animate_bird, so_long);
	mlx_loop(so_long->mlx);
	return (0);
}
