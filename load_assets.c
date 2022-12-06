/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:34:31 by ngalzand          #+#    #+#             */
/*   Updated: 2022/12/05 17:34:35 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	load_bird_textures(t_game *sl)
{
	sl->birdtextures[0] = mlx_load_png("assets/bird_leftside_1.png");
	sl->birdtextures[1] = mlx_load_png("assets/bird_leftside_2.png");
	sl->birdtextures[2] = mlx_load_png("assets/bird_leftside_3.png");
	sl->birdtextures[3] = mlx_load_png("assets/bird_rightside_1.png");
	sl->birdtextures[4] = mlx_load_png("assets/bird_rightside_2.png");
	sl->birdtextures[5] = mlx_load_png("assets/bird_rightside_3.png");
	sl->birdtextures[6] = mlx_load_png("assets/bird_frontside_1.png");
	sl->birdtextures[7] = mlx_load_png("assets/bird_frontside_2.png");
	sl->birdtextures[8] = mlx_load_png("assets/bird_frontside_3.png");
	sl->birdtextures[9] = mlx_load_png("assets/bird_rearside_1.png");
	sl->birdtextures[10] = mlx_load_png("assets/bird_rearside_2.png");
	sl->birdtextures[11] = mlx_load_png("assets/bird_rearside_3.png");
	if (!sl->birdtextures[0] || !sl->birdtextures[1] || !sl->birdtextures[2]
		|| !sl->birdtextures[3] || !sl->birdtextures[4] || !sl->birdtextures[5]
		|| !sl->birdtextures[6] || !sl->birdtextures[7] || !sl->birdtextures[8]
		|| !sl->birdtextures[9] || !sl->birdtextures[10]
		|| !sl->birdtextures[11])
		return (put_error("MLX Failed to load player's textures"));
	return (0);
}

static int	load_wall_textures(t_game *sl)
{
	sl->walltextures[0] = mlx_load_png("assets/wall_bottom.png");
	sl->walltextures[1] = mlx_load_png("assets/wall_bottom_left.png");
	sl->walltextures[2] = mlx_load_png("assets/wall_bottom_right.png");
	sl->walltextures[3] = mlx_load_png("assets/wall_left.png");
	sl->walltextures[4] = mlx_load_png("assets/wall_right.png");
	sl->walltextures[5] = mlx_load_png("assets/wall_top.png");
	sl->walltextures[6] = mlx_load_png("assets/wall_top_left.png");
	sl->walltextures[7] = mlx_load_png("assets/wall_top_right.png");
	if (!sl->walltextures[0] || !sl->walltextures[1] || !sl->walltextures[2]
		|| !sl->walltextures[3] || !sl->walltextures[4] || !sl->walltextures[5]
		|| !sl->walltextures[6] || !sl->walltextures[7])
		return (put_error("MLX Failed to load textures"));
	return (0);
}

static int	load_textures(t_game *sl)
{
	sl->grasstextures = mlx_load_png("assets/grass.png");
	sl->bushtextures[0] = mlx_load_png("assets/bush.png");
	sl->bushtextures[1] = mlx_load_png("assets/flower.png");
	sl->foodtextures[0] = mlx_load_png("assets/berries.png");
	sl->foodtextures[1] = mlx_load_png("assets/grape.png");
	sl->fireplacetextures = mlx_load_png("assets/fireplace_1.png");
	sl->nesttextures = mlx_load_png("assets/nest.png");
	if (!sl->grasstextures || !sl->bushtextures[0] || !sl->bushtextures[1]
		|| !sl->foodtextures[0] || !sl->foodtextures[1] || !sl->nesttextures)
		return (put_error("MLX Failed to load textures"));
	return (0);
}

static int	load_images(t_game *sl)
{
	long int	i;

	i = -1;
	while (++i <= 7)
		sl->wall[i] = mlx_texture_to_image(sl->mlx, sl->walltextures[i]);
	i = -1;
	sl->fireplace = mlx_texture_to_image(sl->mlx, sl->fireplacetextures);
	sl->grass = mlx_texture_to_image(sl->mlx, sl->grasstextures);
	sl->bush[0] = mlx_texture_to_image(sl->mlx, sl->bushtextures[0]);
	sl->bush[1] = mlx_texture_to_image(sl->mlx, sl->bushtextures[1]);
	sl->food[0] = mlx_texture_to_image(sl->mlx, sl->foodtextures[0]);
	sl->food[1] = mlx_texture_to_image(sl->mlx, sl->foodtextures[1]);
	sl->nest = mlx_texture_to_image(sl->mlx, sl->nesttextures);
	sl->bird = mlx_texture_to_image(sl->mlx, sl->birdtextures[0]);
	sl->bird_actual_texture = 0;
	return (0);
}

int	load_assets(t_game *so_long)
{
	if (load_textures(so_long) == -1
		|| load_wall_textures(so_long) == -1
		|| load_bird_textures(so_long) == -1)
		return (-1);
	load_images(so_long);
	return (0);
}
