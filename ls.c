/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:34:21 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 16:27:20 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

t_node	*ft_opendir(t_opt *opt, t_path *path, DIR *current_dir)
{
	struct dirent	*current_file;
	t_node			*root;

	root = NULL;
	CURRENT_PATH = ft_addpath(CURRENT_PATH, "/", 'L');
	while ((current_file = readdir(current_dir)))
	{
		if (current_file->d_name[0] == '.' && !(opt->opt_a))
			continue;
		PATH_TMP = ft_addpath(CURRENT_PATH, current_file->d_name, 'N');
		if (errno != 0)
			ft_error(errno, path, opt);
		if (!root)
			root = ft_create_node(current_file, PATH_TMP, opt);
		else
			ft_place_node(&root,
		ft_create_node(current_file, PATH_TMP, opt), opt);
		ft_strdel(&PATH_TMP);
	}
	return (root);
}

t_node	*ft_ls(t_opt *opt, t_path *path)
{
	DIR				*current_dir;
	t_node			*root;

	errno = 0;
	root = NULL;
	if ((current_dir = opendir(CURRENT_PATH)))
	{
		if (path->dir_or_file != DIRECTORY)
		{
			closedir(current_dir);
			return (root);
		}
		root = ft_opendir(opt, path, current_dir);
		closedir(current_dir);
	}
	if (errno == ENOTDIR || errno == ENOENT)
		return (ft_error2(path, opt));
	ft_display_ls(opt, path, root);
	if (opt->opt_upperr && path->dir_or_file == DIRECTORY)
	{
		path->sub_index = 1;
		ft_recursivels(root, opt, path);
	}
	ft_free_tree(&root, opt);
	return (NULL);
}

void	ft_lserror(t_opt *opt, t_path *path)
{
	DIR			*current_dir;

	if ((current_dir = opendir(CURRENT_PATH)))
		closedir(current_dir);
	else
		ft_error2(path, opt);
}

void	ft_lsfile(t_opt *opt, t_path *path)
{
	t_node	*root;
	t_node	*node;
	char	spaceat_theend;

	root = NULL;
	spaceat_theend = 0;
	while (CURRENT_PATH)
	{
		node = ft_ls(opt, path);
		if (!root && node)
			root = node;
		else if (node)
			ft_place_node(&root, node, opt);
		if (!errno)
			spaceat_theend = 1;
		path->index++;
	}
	if (root)
		ft_display_tree(root, opt);
	if (opt->opt_l)
		ft_resetspaces();
	if (spaceat_theend && root)
		ft_putchar('\n');
	ft_free_tree(&root, opt);
}

void	ft_start_ls(t_opt *opt, t_path *path)
{
	path->dir_or_file = ERROR;
	while (CURRENT_PATH)
	{
		ft_lserror(opt, path);
		path->index++;
	}
	ft_sortargv(path, opt);
	path->index = 0;
	path->dir_or_file = FILE;
	ft_lsfile(opt, path);
	path->dir_or_file = DIRECTORY;
	path->index = 0;
	while (CURRENT_PATH)
	{
		ft_ls(opt, path);
		path->index++;
	}
}
