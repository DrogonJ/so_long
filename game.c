/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:34:12 by ngalzand          #+#    #+#             */
/*   Updated: 2022/12/05 17:34:19 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move(t_game *sl)
{
	if (mlx_is_key_down(sl->mlx, MLX_KEY_D)
		&& sl->map[sl->playerpos.y][sl->playerpos.x + 1] != '1')
		move_bird(sl, 3, "+x");
	else if (mlx_is_key_down(sl->mlx, MLX_KEY_A)
		&& sl->map[sl->playerpos.y][sl->playerpos.x - 1] != '1')
		move_bird(sl, 0, "-x");
	else if (mlx_is_key_down(sl->mlx, MLX_KEY_W)
		&& sl->map[sl->playerpos.y - 1][sl->playerpos.x] != '1')
		move_bird(sl, 9, "-y");
	else if (mlx_is_key_down(sl->mlx, MLX_KEY_S)
		&& sl->map[sl->playerpos.y + 1][sl->playerpos.x] != '1')
		move_bird(sl, 6, "+y");
}

void	game(mlx_key_data_t keydata, void *params)
{
	t_game	*sl;

	sl = params;
	(void)keydata;
	if (mlx_is_key_down(sl->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(sl->mlx);
	move(sl);
	if (sl->map[sl->playerpos.y][sl->playerpos.x] == 'C')
	{
		sl->map[sl->playerpos.y][sl->playerpos.x] = 0;
		sl->foodcount--;
		mlx_image_to_window(sl->mlx, sl->grass,
			sl->playerpos.x * 64, sl->playerpos.y * 64);
	}
	if (sl->map[sl->playerpos.y][sl->playerpos.x] == 'V')
		putmsg_and_close(sl, "Game over...\n");
	if (sl->foodcount == 0)
	{
		sl->foodcount = -1;
		mlx_image_to_window(sl->mlx, sl->nest,
			sl->nestpos.x * 64, sl->nestpos.y * 64);
	}
	if (sl->foodcount == -1 && sl->playerpos.x == sl->nestpos.x
		&& sl->playerpos.y == sl->nestpos.y)
		putmsg_and_close(sl, "You won the game!\n");
}
