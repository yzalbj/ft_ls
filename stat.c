/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 11:47:36 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 19:07:09 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	stat_optl2(char *path, t_stat *return_stat, struct stat *current_stat)
{
	if (return_stat->mode[0] == 'c' || return_stat->mode[0] == 'b')
	{
		return_stat->size[0] = major(current_stat->st_rdev);
		return_stat->size[1] = minor(current_stat->st_rdev);
	}
	else
	{
		return_stat->size[0] = 0;
		return_stat->size[1] = current_stat->st_size;
	}
	ft_calc_blocks(current_stat->st_blocks, 0);
	ft_spacebeforenlink(return_stat->nlink, 0);
	ft_spacebeforenbytes(return_stat->size[0], 0, return_stat->mode[0], 0);
	ft_spacebeforenbytes(return_stat->size[1], 0, return_stat->mode[0], 1);
	if (return_stat->mode[0] == 'l')
	{
		return_stat->readlink = ft_strnew(4095);
		readlink(path, return_stat->readlink, 4095);
	}
}

void	stat_optl1(char *path, t_stat *return_stat, struct stat *current_stat)
{
	struct group	*current_group;
	struct passwd	*current_user;

	current_group = getgrgid(current_stat->st_gid);
	return_stat->group = ft_strdup(current_group->gr_name);
	current_user = getpwuid(current_stat->st_uid);
	return_stat->user = ft_strdup(current_user->pw_name);
	return_stat->nlink = current_stat->st_nlink;
	ft_spaceafteruser(return_stat->user, 0);
	ft_spaceaftergroup(return_stat->group, 0);
	stat_optl2(path, return_stat, current_stat);
}

void	stat_time(t_stat *return_stat, struct stat *current_stat)
{
	char **year;

	return_stat->epoch_sec = current_stat->st_mtimespec.tv_sec;
	return_stat->epoch_nsec = current_stat->st_mtimespec.tv_nsec;
	return_stat->time =
		ft_strsub(ctime(&(current_stat->st_mtimespec.tv_sec)), 4, 16);
	year = ft_strsplit(ctime(&(return_stat->epoch_sec)), ' ');
	return_stat->year = ft_strtrim(year[4]);
	ft_freetab(&year);
}

t_stat	*ft_create_stat(struct dirent *file, char *path, t_opt *opt)
{
	t_stat			*return_stat;
	struct stat		*current_stat;

	if (!(current_stat = (struct stat *)malloc(sizeof(struct stat))))
		return (NULL);
	if (!(return_stat = (t_stat *)malloc(sizeof(t_stat))))
		return (NULL);
	if ((lstat(path, current_stat)) == -1)
	{
		free(return_stat);
		free(current_stat);
		return (NULL);
	}
	stat_time(return_stat, current_stat);
	if (file)
		return_stat->name = ft_strdup(file->d_name);
	else
		return_stat->name = ft_strdup(path);
	return_stat->mode = ft_findmode(current_stat->st_mode);
	if (opt->opt_l)
		stat_optl1(path, return_stat, current_stat);
	free(current_stat);
	return (return_stat);
}
