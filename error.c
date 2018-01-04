/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:29:27 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 16:01:49 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

t_node	*ft_error2(t_path *path, t_opt *opt)
{
	t_node		*node_file;
	struct stat	tmp;

	node_file = NULL;
	if (!(lstat(CURRENT_PATH, &tmp)))
		node_file = ft_create_node(NULL, CURRENT_PATH, opt);
	if (path->dir_or_file == FILE)
	{
		if (errno == ENOTDIR || (node_file && node_file->stat->mode[0] == 'l'))
			return (node_file);
	}
	else if (errno == ENOENT && path->dir_or_file == ERROR &&
			(!node_file || node_file->stat->mode[0] != 'l'))
	{
		ft_putstr_fd("ft_ls: ", 2);
		if (!(ft_strcmp(CURRENT_PATH, "")))
			ft_putstr_fd("fts_open", 2);
		else
			ft_putstr_fd(CURRENT_PATH, 2);
		ft_putendl_fd(": No such file or directory", 2);
		path->error[path->index] = 1;
	}
	if (node_file)
		ft_free_node(&node_file, opt);
	return (NULL);
}

void	ft_error(int err, t_path *path, t_opt *opt)
{
	if (err == FALSE_OPT)
		ft_putendl_fd("usage: ft_ls [-1RTalrt] [file ...]", 2);
	if (errno == EACCES && path->dir_or_file == DIRECTORY)
	{
		ft_putstr_fd("ft_ls: ", 2);
		if (PATH_TMP)
			ft_putstr_fd(ft_lastfile(PATH_TMP), 2);
		else
			ft_putstr_fd(ft_lastfile(CURRENT_PATH), 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	if (path && opt)
		ft_error2(path, opt);
}
