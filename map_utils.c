/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:24:03 by ngalzand          #+#    #+#             */
/*   Updated: 2022/12/05 17:37:39 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	food_and_villain_count(t_game *sl)
{
	size_t	y;
	size_t	x;

	y = 0;
	sl->foodcount = 0;
	sl->villaincount++;
	while (sl->map[y])
	{
		x = 0;
		while (sl->map[y][x])
		{
			if (sl->map[y][x] == 'C')
				sl->foodcount++;
			if (sl->map[y][x] == 'V')
				sl->villaincount++;
			x++;
		}
		y++;
	}
}

size_t	ft_strlen_sl(const char *s)
{
	size_t	count;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != '\n')
			count++;
		i++;
	}
	return (count);
}

t_pos	getpos(char **map, char c)
{
	size_t	x;
	size_t	y;
	t_pos	res;

	y = 0;
	res.x = 0;
	res.y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == c)
			{
				res.x = x;
				res.y = y;
				return (res);
			}
			x++;
		}
		y++;
	}
	return (res);
}

void	check_elem(char c, unsigned int **elements)
{
	if (c == 'C')
		elements[0][0] += 1;
	else if (c == 'E')
		elements[0][1] += 1;
	else if (c == 'P')
		elements[0][2] += 1;
}

char	*ft_strdup_sl(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	i = 0;
	len = ft_strlen_sl(s1);
	ptr = malloc((len * sizeof(char)) + 1);
	if (!ptr)
		return (0);
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
