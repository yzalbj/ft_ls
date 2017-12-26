/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:05:00 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/18 14:05:01 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

char	ft_spacebeforenlink(int nlink, int reset)
{
	static char	space;
	char 		tmp;

	tmp = ft_intlen(nlink);
	if (tmp > space)
		space = tmp;
	tmp = space;
	if (reset)
		space = 0;
	return (tmp);
}

char	ft_spacebeforenbytes(int size, int reset)
{
	static char	space;
	char 		tmp;

	tmp = ft_intlen(size);
	if (tmp > space)
		space = tmp;
	tmp = space;
	if (reset)
		space = 0;
	return (tmp);
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

int		ft_spaceafteruser(char  *user, int reset)
{
	static char space;
	char tmp;

	tmp = ft_strlen(user);
	if (tmp > space)
		space = tmp;
	tmp = space;
	if (reset)
		space = 0;
	return(tmp);
}

int		ft_spaceaftergroup(char  *group, int reset)
{
	static char space;
	char tmp;

	tmp = ft_strlen(group);
	if (tmp > space)
		space = tmp;
	tmp = space;
	if (reset)
		space = 0;
	return(tmp);
}
