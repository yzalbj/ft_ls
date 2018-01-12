/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 19:19:10 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/08 18:11:11 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

int		ft_major(dev_t x)
{
	return ((x >> 24) & 0xff);
}

int		ft_minor(dev_t x)
{
	return ((x) & 0xffffff);
}

int		ft_checksymlink(t_node **node, t_opt *opt, t_path *path)
{
	t_node	*checklink;

	checklink = ft_create_node(NULL, CURRENT_PATH, opt);
	if (checklink && checklink->stat->mode[0] == 'l' && CURRENT_PATH
		&& !path->sub_index && opt->opt_l)
	{
		*node = checklink;
		return (1);
	}
	if (checklink)
		ft_free_node(&checklink, opt);
	*node = NULL;
	return (0);
}
