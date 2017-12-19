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

// char	*ft_findtype(mode_t st_mode, char *mode, char sticky_bit)
// {
// 	int		len;
// 	int		*oct;
//
// 	len = 0;
// 	oct = ft_dectooct(st_mode);
// 	ft_putstr("oct == ");
// 	while (oct[len] != -1)
// 	{
// 		ft_putnbr(oct[len]);
// 		len++;
// 	}
// 	ft_putchar('\n');
// 	len = 0;
// 	sticky_bit = 0;
// 	if (st_mode & S_IRGRP)
// 	{
// 		ft_putendl("group read");
// 	}
// 	// while (oct[len + 1] != -1)
// 	// 	len++;
// 	// if (len == 5 && oct[len] == 1 && oct[len - 1] == 0 && oct[len - 2] == 0)
// 	// 	mode[0] = '-';
// 	// else if (oct[len] == 1 && oct[len - 1] == 2 && oct[len - 2] == 0)
// 	// 	mode[0] = 'l';
// 	// else if (oct[len] == 1 && oct[len - 1] == 4 && oct[len - 2] == 0)
// 	// 	mode[0] = 's';
// 	// else if (oct[len] == 1 && oct[len - 1] == 6 && oct[len - 2] == 0)
// 	// 	mode[0] = 'w';
// 	// // if (oct[len - 2] == 1)
// 	// // 	mode[9] = 't';
// 	// else if (oct[len] == 1 && oct[len - 1] == 0)
// 	// 	mode[0] = 'p';
// 	// else if (oct[len] == 2 && oct[len - 1] == 0)
// 	// 	mode[0] = 'c';
// 	// else if (oct[len] == 4 && (oct[len - 1] == 0 || sticky_bit))
// 	// 	mode[0] = 'd';
// 	// else if (oct[len] == 6 && oct[len - 1] == 0)
// 	// 	mode[0] = 'b';
// 	// if (oct[len - 1] == 1)
// 	// 	mode[9] = 't';
// 	free(oct);
// 	return (mode);
// }

char	*ft_findmode(mode_t st_mode)
{
	char	*mode;
	int		i;

	mode = ft_strnew(10);

		if ((st_mode & S_IFLNK) == S_IFLNK)
			mode[0] = 'l';
		else if ((st_mode & S_IFSOCK) == S_IFSOCK)
			mode[0] = 's';
		else if ((st_mode & S_IFWHT) == S_IFWHT)
			mode[0] = 'w';
		else if ((st_mode & S_IFIFO) == S_IFIFO)
			mode[0] = 'p';
		else if ((st_mode & S_IFCHR) == S_IFCHR)
			mode[0] = 'c';
		else if ((st_mode & S_IFDIR) == S_IFDIR)
			mode[0] = 'd';
		else if ((st_mode & S_IFBLK) == S_IFBLK)
			mode[0] = 'b';
		else if ((st_mode & S_IFREG) == S_IFREG)
				mode[0] = '-';
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

t_stat  *ft_create_stat(struct dirent *file, char *path, t_opt *opt)
{
    t_stat          *return_stat;
    struct stat     *current_stat;
    struct group    *current_group;
    struct passwd   *current_user;

    if (!(current_stat = (struct stat *)malloc(sizeof(struct stat))))
        return (NULL);
    if (!(return_stat = (t_stat *)malloc(sizeof(t_stat))))
        return (NULL);
	printf("path stat = %s\n", path);
	if ((lstat(path, current_stat)))
	{
		return (NULL);
		ft_putendl("Error when using stat() ;");
		printf("with this path -> %s\n", path);
		exit (0);
	}
    current_group = getgrgid(current_stat->st_gid);
    return_stat->group = ft_strdup(current_group->gr_name);
    current_user = getpwuid(current_stat->st_uid);
    return_stat->user = ft_strdup(current_user->pw_name);
	return_stat->epoch = current_stat->st_mtimespec.tv_sec;
	if (file)
		return_stat->name = ft_strdup(file->d_name);
	else
		return_stat->name = path;
	// printf("name = %s\n", return_stat->name);
	return_stat->mode = ft_findmode(current_stat->st_mode);
	return_stat->time = ft_strsub(ctime(&(current_stat->st_mtimespec.tv_sec)), 4, 20);
	if (opt->opt_l)
	{
		return_stat->nlink = current_stat->st_nlink;
		return_stat->size = current_stat->st_size;
		ft_spaceafteruser(return_stat->user, 0);
		ft_spaceaftergroup(return_stat->group, 0);
		ft_calc_blocks(current_stat->st_blocks, 0);
		ft_spacebeforenlink(return_stat->nlink, 0);
		ft_spacebeforenbytes(return_stat->size, 0);
		if (return_stat->mode[0] == 'l')
		{
			return_stat->readlink = ft_strnew(4095);
			readlink(path, return_stat->readlink, 4095);
		}
	}
	//free(current_user);
	//free(current_group);
	free(current_stat);
	return (return_stat);
}
