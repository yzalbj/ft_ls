/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 19:07:18 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 19:07:20 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	ft_findtype(mode_t st_mode, char *mode)
{
	if ((st_mode & S_IFLNK) == S_IFLNK)
		mode[0] = 'l';
	else if ((st_mode & S_IFSOCK) == S_IFSOCK)
		mode[0] = 's';
	else if ((st_mode & S_IFWHT) == S_IFWHT)
		mode[0] = 'w';
	else if ((st_mode & S_IFIFO) == S_IFIFO)
		mode[0] = 'p';
	else if ((st_mode & S_IFBLK) == S_IFBLK)
		mode[0] = 'b';
	else if ((st_mode & S_IFCHR) == S_IFCHR)
		mode[0] = 'c';
	else if ((st_mode & S_IFDIR) == S_IFDIR)
		mode[0] = 'd';
	else if ((st_mode & S_IFREG) == S_IFREG)
		mode[0] = '-';
}

void	ft_findperm(mode_t st_mode, char *mode)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		if (((st_mode & S_IRUSR) && i == 0) || ((st_mode & S_IRGRP) && i == 1)
			|| ((st_mode & S_IROTH) && i == 2))
			mode[1 + i * 3] = 'r';
		else
			mode[1 + i * 3] = '-';
		if (((st_mode & S_IWUSR) && i == 0) || ((st_mode & S_IWGRP) && i == 1)
			|| ((st_mode & S_IWOTH) && i == 2))
			mode[2 + i * 3] = 'w';
		else
			mode[2 + i * 3] = '-';
		if (((st_mode & S_IXUSR) && i == 0) || ((st_mode & S_IXGRP) && i == 1)
			|| ((st_mode & S_IXOTH) && i == 2))
			mode[3 + i * 3] = 'x';
		else
			mode[3 + i * 3] = '-';
		i++;
	}
}

char	*ft_findmode(mode_t st_mode)
{
	char	*mode;

	mode = ft_strnew(10);
	ft_findtype(st_mode, mode);
	ft_findperm(st_mode, mode);
	if ((st_mode & S_ISVTX) && !(st_mode & S_IXOTH))
		mode[9] = 'T';
	else if (st_mode & S_ISVTX)
		mode[9] = 't';
	if ((st_mode & S_ISUID) && !(st_mode & S_IXUSR))
		mode[3] = 'S';
	else if (st_mode & S_ISUID)
		mode[3] = 's';
	if ((st_mode & S_ISGID) && !(st_mode & S_IXGRP))
		mode[6] = 'S';
	else if (st_mode & S_ISGID)
		mode[6] = 's';
	return (mode);
}
