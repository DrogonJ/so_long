/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:34:27 by ngalzand          #+#    #+#             */
/*   Updated: 2022/12/06 10:31:46 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	put_error(char *error_message)
{
	ft_putstr_fd("Error:\n", 2);
	ft_putstr_fd(error_message, 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

int	free_and_return(void *v1, void *v2, void *v3, char *errormessage)
{
	if (v1)
		free(v1);
	if (v2)
		free(v2);
	if (v3)
		free(v3);
	if (errormessage)
	{
		if (errormessage[0])
			return (put_error(errormessage));
		else
			return (-1);
	}
	return (0);
}

int	free_so_long(t_game *so_long)
{
	if (!so_long)
		return (0);
	if (so_long->map)
		so_long->map = freestrtab(so_long->map, tablen(so_long->map));
	if (so_long->mlx)
		mlx_terminate(so_long->mlx);
	free(so_long);
	return (0);
}

char	**lstclearreturn(t_list *lst)
{
	ft_lstclear((t_list **)&lst, &free);
	return (0);
}
