/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gestion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:23:58 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/29 16:24:00 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

long int	tablen(char **map)
{
	long int	counter;

	counter = 0;
	while (map[counter])
		counter++;
	return (counter);
}

void	*freestrtab(char **str, size_t indice)
{
	size_t	i;

	i = 0;
	while (i < indice)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static t_list	*ft_lstnew_sl(void *content, void (*del)(void *))
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
	{
		(*del)(content);
		return (0);
	}
	ptr->content = content;
	ptr->next = 0;
	return (ptr);
}

static t_list	*get_linkedlst_map(int fd)
{
	t_list	*map;
	t_list	*curr;

	map = ft_lstnew_sl(get_next_line(fd), &free);
	if (!map)
		return (0);
	curr = map;
	while (curr->content)
	{
		curr = curr->next;
		curr = ft_lstnew_sl(get_next_line(fd), &free);
		if (!curr)
		{
			ft_lstclear(&map, &free);
			return (0);
		}
		ft_lstadd_back(&map, curr);
	}
	return (map);
}

char	**get_map(int fd)
{
	const t_list	*linkedmap = get_linkedlst_map(fd);
	char			**map;
	t_list			*curr;
	long int		lines;
	long int		i;

	if (!linkedmap)
		return (0);
	lines = ft_lstsize((t_list *)linkedmap);
	map = (char **)ft_calloc(lines, sizeof(char *));
	if (!map)
		return (lstclearreturn((t_list *)linkedmap));
	curr = (t_list *)linkedmap;
	i = -1;
	while (++i < lines && curr->content != 0)
	{
		map[i] = ft_strdup_sl(curr->content);
		if (!map[i])
			return (freestrtab(map, i));
		curr = curr->next;
	}
	ft_lstclear((t_list **)&linkedmap, &free);
	return (map);
}
