/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:05:00 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/03 19:46:51 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	ft_resetspaces(void)
{
	ft_spaceafteruser("", 1);
	ft_spaceaftergroup("", 1);
	ft_spacebeforenlink(0, 1);
	ft_spacebeforenbytes(0, 1);
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

char	ft_spacebeforenbytes(int size, int reset)
{
	static char	space;
	char		tmp;

	tmp = ft_intlen(size);
	if (tmp > space)
		space = tmp;
	tmp = space;
	if (reset)
		space = 0;
	return (tmp);
}

int		ft_spaceafteruser(char *user, int reset)
{
	static char space;
	char		tmp;

	tmp = ft_strlen(user);
	if (tmp > space)
		space = tmp;
	tmp = space;
	if (reset)
		space = 0;
	return (tmp);
}

int		ft_spaceaftergroup(char *group, int reset)
{
	static char space;
	char		tmp;

	tmp = ft_strlen(group);
	if (tmp > space)
		space = tmp;
	tmp = space;
	if (reset)
		space = 0;
	return (tmp);
}
