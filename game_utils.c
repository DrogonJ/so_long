/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:34:21 by ngalzand          #+#    #+#             */
/*   Updated: 2022/12/06 10:31:28 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	change_bird_texture(t_game *sl, size_t indice)
{
	mlx_delete_image(sl->mlx, sl->bird);
	sl->bird = mlx_texture_to_image(sl->mlx,
			sl->birdtextures[sl->bird_actual_texture + indice]);
	mlx_image_to_window(sl->mlx, sl->bird,
		sl->playerpos.x * 64, sl->playerpos.y * 64);
}

void	animate_bird(void *params)
{
	static long int	n = 0;
	t_game			*sl;

	sl = params;
	if (n == FRAMESPEED || n == FRAMESPEED * 3)
		change_bird_texture(sl, 1);
	if (n == FRAMESPEED * 2)
		change_bird_texture(sl, 2);
	if (n == FRAMESPEED * 4)
	{
		change_bird_texture(sl, 0);
		n = -1;
	}
	n++;
}

void	display_steps(t_game *sl)
{
	char	*string;

	mlx_delete_image(sl->mlx, sl->stepstring);
	string = ft_strdup("Steps: ");
	string = ft_strjoin_gnl(string, ft_itoa(sl->step));
	string = ft_strjoin_gnl(string, "\n");
	sl->stepstring = mlx_put_string(sl->mlx, string, 60, 40);
	free(string);
}

void	move_bird(t_game *sl, size_t indice, char *pos)
{
	if (pos[0] == '+' && pos[1] == 'x')
		sl->playerpos.x++;
	if (pos[0] == '+' && pos[1] == 'y')
		sl->playerpos.y++;
	if (pos[0] == '-' && pos[1] == 'x')
		sl->playerpos.x--;
	if (pos[0] == '-' && pos[1] == 'y')
		sl->playerpos.y--;
	mlx_delete_image(sl->mlx, sl->bird);
	sl->bird = mlx_texture_to_image(sl->mlx,
			sl->birdtextures[indice]);
	sl->bird_actual_texture = indice;
	mlx_image_to_window(sl->mlx, sl->bird,
		sl->playerpos.x * 64, sl->playerpos.y * 64);
	sl->step++;
	display_steps(sl);
}

void	putmsg_and_close(t_game *sl, char *msg)
{
	ft_putstr_fd(msg, 1);
	mlx_close_window(sl->mlx);
}
