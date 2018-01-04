/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:05:00 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 15:53:17 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	ft_resetspaces(void)
{
	ft_spaceafteruser("", 1);
	ft_spaceaftergroup("", 1);
	ft_spacebeforenlink(0, 1);
	ft_spacebeforenbytes(0, 1, 0, 0);
}

char	ft_spacebeforenlink(int nlink, int reset)
{
	static char	space;
	char		tmp;

	tmp = ft_intlen(nlink);
	if (tmp > space)
		space = tmp;
	if (reset)
		space = 0;
	return (space);
}

char	ft_spacebeforenbytes(int size, int reset, char mode, int index)
{
	static char	space[2];
	char		tmp[2];

	if (index == 0 && (mode == 'c' || mode == 'b'))
	{
		tmp[0] = ft_intlen(size);
		if (tmp[0] > space[0])
			space[0] = tmp[0];
	}
	else if (index == 1)
	{
		tmp[1] = ft_intlen(size);
		if (tmp[1] > space[1])
			space[1] = tmp[1];
	}
	if (reset)
	{
		space[0] = 0;
		space[1] = 0;
	}
	return (space[index]);
}

int		ft_spaceafteruser(char *user, int reset)
{
	static char space;
	char		tmp;

	tmp = ft_strlen(user);
	if (tmp > space)
		space = tmp;
	if (reset)
		space = 0;
	return (space);
}

int		ft_spaceaftergroup(char *group, int reset)
{
	static char space;
	char		tmp;

	tmp = ft_strlen(group);
	if (tmp > space)
		space = tmp;
	if (reset)
		space = 0;
	return (space);
}
