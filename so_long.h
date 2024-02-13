/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:24:10 by ngalzand          #+#    #+#             */
/*   Updated: 2024/02/13 11:32:19 by checkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./Libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "./MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

# define FRAMESPEED 10

typedef struct s_pos
{
	size_t	x;
	size_t	y;
}	t_pos;

typedef struct s_game
{
	mlx_t			*mlx;
	char			**map;
	t_pos			playerpos;
	t_pos			nestpos;
	size_t			bird_actual_texture;
	unsigned int	step;
	long int		foodcount;
	long int		villaincount;
	mlx_image_t		*stepstring;
	mlx_texture_t	*birdtextures[12];
	mlx_texture_t	*grasstextures;
	mlx_texture_t	*bushtextures[2];
	mlx_texture_t	*walltextures[8];
	mlx_texture_t	*foodtextures[2];
	mlx_texture_t	*fireplacetextures;
	mlx_texture_t	*nesttextures;
	mlx_image_t		*bird;
	mlx_image_t		*grass;
	mlx_image_t		*bush[2];
	mlx_image_t		*wall[8];
	mlx_image_t		*food[2];
	mlx_image_t		*fireplace;
	mlx_image_t		*nest;
}	t_game;

int			check_map(char *path);
int			put_error(char *error_message);
char		**get_map(int fd);
int			check_map(char *path);
void		*freestrtab(char **str, size_t indice);
long int	tablen(char **map);
size_t		ft_strlen_sl(const char *s);
void		food_and_villain_count(t_game *sl);
void		check_elem(char c, unsigned int **elements);
char		*ft_strdup_sl(const char *s1);
t_pos		getpos(char **map, char c);
int			free_and_return(void *v1, void *v2, void *v3, char *errormessage);
void		move_bird(t_game *sl, size_t indice, char *pos);
int			start_game(t_game *so_long);
void		game(mlx_key_data_t keydata, void *params);
void		animate_bird(void *params);
void		animate_campfire(void *params);
int			load_assets(t_game *so_long);
int			free_so_long(t_game *so_long);
void		putmsg_and_close(t_game *sl, char *msg);
void		display_steps(t_game *sl);
char		**lstclearreturn(t_list *lst);

#endif
