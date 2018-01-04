/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 19:17:43 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 19:18:56 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

/*
** si FT_TIMECMP == 1 alors le temps de node est PLUS RECENT que celui de root
** si FT_TIMECMP == -1 alors le temps de node est PLUS VIEUX que celui de root
** si FT_TIMECMP == 0 alors le temps de node est EGAL a celui de root
*/

int		ft_timecmp(t_stat *root, t_stat *node)
{
	if (root->epoch_sec < node->epoch_sec)
		return (1);
	else if (root->epoch_sec > node->epoch_sec)
		return (-1);
	else if (root->epoch_nsec < node->epoch_nsec)
		return (1);
	else if (root->epoch_nsec > node->epoch_nsec)
		return (-1);
	else
		return (0);
}

char	*ft_lastfile(char *path)
{
	int		len;

	len = ft_strlen(path);
	while (len >= 0)
	{
		if (path[len] == '/')
			break ;
		len--;
	}
	return (&path[len + 1]);
}

void	ft_printwithoutslash(char *path)
{
	char	*new;

	if (path && path[ft_strlen(path) - 1] == '/')
	{
		new = ft_strnew(ft_strlen(path) - 1);
		ft_strncpy(new, path, ft_strlen(path) - 1);
		ft_putstr(new);
		ft_strdel(&new);
	}
	else if (path)
		ft_putstr(path);
}

char	*ft_addpath(char *path, char *to_add, char part_free)
{
	char *new;

	new = ft_strjoin(path, to_add, part_free);
	return (new);
}

int		ft_calc_blocks(int blocks, int reset)
{
	static int	total;
	int			tmp;

	total += blocks;
	tmp = total;
	if (reset)
		total = 0;
	return (tmp);
}
