/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 11:47:36 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/15 11:47:39 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

char	*ft_findtype(mode_t st_mode, char *mode)
{
	int		len;
	int		*oct;

	len = 0;
	oct = ft_dectooct(st_mode);
	while (oct[len + 1] != -1)
		len++;
	if (len == 5 && oct[len] == 1 && oct[len - 1] == 0 && oct[len - 2] == 0)
		mode[0] = '-';
	else if (oct[len] == 1 && oct[len - 1] == 2 && oct[len - 2] == 0)
		mode[0] = 'l';
	else if (oct[len] == 1 && oct[len - 1] == 4 && oct[len - 2] == 0)
		mode[0] = 's';
	else if (oct[len] == 1 && oct[len - 1] == 6 && oct[len - 2] == 0)
		mode[0] = 'w';
	else if (oct[len] == 1 && oct[len - 1] == 0)
		mode[0] = 'p';
	else if (oct[len] == 2 && oct[len - 1] == 0)
		mode[0] = 'c';
	else if (oct[len] == 4 && oct[len - 1] == 0)
		mode[0] = 'd';
	else if (oct[len] == 6 && oct[len - 1] == 0)
		mode[0] = 'b';
	free(oct);
	return (mode);
}

char	*ft_findmode(mode_t st_mode)
{
	int		*binary;
	char	*mode;
	int		len;
	int		tmp;

	binary = ft_dectobin(st_mode);
	mode = ft_strnew(10);
	len = 0;
	tmp = 8;
	while (tmp >= 0)
	{
		if (binary[len++] == 1)
		{
			if (tmp % 3 == 2)
				mode[tmp + 1] = 'x';
			if (tmp % 3 == 1)
				mode[tmp + 1] = 'w';
			if (tmp % 3 == 0)
				mode[tmp + 1] = 'r';
		}
		else
			mode[tmp + 1] = '-';
		tmp--;
	}
	ft_findtype(st_mode, mode);
	free(binary);
	return (mode);
}

t_stat  *ft_create_stat(struct dirent *file, const char *path)
{
    t_stat          *return_stat;
    time_t          time_tmp;
    struct stat     *current_stat;
    struct group    *current_group;
    struct passwd   *current_user;

    if (!(current_stat = (struct stat *)malloc(sizeof(struct stat))))
        return (NULL);
    if (!(return_stat = (t_stat *)malloc(sizeof(t_stat))))
        return (NULL);

	if ((lstat(path, current_stat)))
	{
		ft_putendl("Error when using stat() ;");
		return (0);
	}
    current_group = getgrgid(current_stat->st_gid);
    return_stat->group = ft_strdup(current_group->gr_name);
    current_user = getpwuid(current_stat->st_uid);
    return_stat->user = ft_strdup(current_user->pw_name);
    return_stat->nlink = current_stat->st_nlink;
    return_stat->name = ft_strdup(file->d_name);
    return_stat->mode = ft_findmode(current_stat->st_mode);
	time_tmp = time(&current_stat->st_atimespec.tv_sec);
    return_stat->time = ft_strsub(ctime(&time_tmp), 4, 12);
	//free(current_user);
	//free(current_group);
	free(current_stat);
	return (return_stat);
}