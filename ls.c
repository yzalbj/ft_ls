/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:34:21 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/14 17:34:23 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

char    *ft_addpath(char *path, char *to_add)
{
    path = ft_strjoin(path, to_add, 'N');
    return (path);
}

char    *ft_removeslash(char *path)
{
    char    *new;

    // ft_putendl(path);
    // ft_putendl("oui");
    if (!path)
      return (NULL);
    if (path[ft_strlen(path) - 1] == '/')
    {
        // ft_putendl("oui");
      new = ft_strnew(ft_strlen(path) - 1);
      ft_strncpy(new, path, ft_strlen(path) - 1);
      return (new);
    }
    return(path);
}

void ft_issymlink(t_opt *opt, t_stat *stat)
{
	if (stat->mode[0] == 'l')
	{
		ft_display_file(opt, stat);
		exit (1);
	}
}

char *ft_lastfile(char *path)
{
	int		len;

	len = ft_strlen(path);
	while (len >= 0)
	{
		if (path[len] == '/')
			break ;
		len--;
	}
	return (&path[len + 1]);
}

void ft_display_ls(t_opt *opt, t_path *path, t_node *root)
{
	static char flag;

	if ((!errno || errno == EACCES) && CURRENT_PATH
		&& path->dir_or_file == DIRECTORY && (path->argc -1 - opt->opt_nb > 1 || path->sub_index))
	{
		// printf("path->index == %d\nopt->opt_nb == %d\n", path->index, opt->opt_nb);
		// ft_putnbr(path->index - opt->opt_nb);
		if (path->sub_index || (!root && path->sub_index))
			ft_putchar('\n');
		ft_putstr(ft_removeslash(CURRENT_PATH));
		ft_putstr(":\n");
	}
	if (errno != 0)
		ft_error(errno, path, opt);
	else
	{
		if (opt->opt_l && root)
		{
			ft_putstr("total ");
			ft_putnbr(ft_calc_blocks(0, 1));
			ft_putchar('\n');
		}
		path->sub_index++;
		ft_display_tree(root, opt);
		if (opt->opt_l)
		{
			ft_spaceafteruser("", 1);
			ft_spaceaftergroup("", 1);
			ft_spacebeforenlink(0, 1);
			ft_spacebeforenbytes(0, 1);
		}
		flag = 1;
		// ft_free_tree(root, opt);
	}
}

t_node *ft_ls(t_opt *opt, t_path *path)
{
	DIR             *current_dir;
	struct dirent   *current_file;
	t_node          *root;

	root = NULL;
	errno = 0;
	if ((current_dir = opendir(CURRENT_PATH)))
	{
		if (path->dir_or_file != DIRECTORY)
		{
			closedir(current_dir);
			return (root);
		}
		if (opt->opt_l)
			ft_issymlink(opt, ft_create_stat(NULL, CURRENT_PATH, opt));
		CURRENT_PATH = ft_addpath(CURRENT_PATH, "/");
		while ((current_file = readdir(current_dir)))
		{
			if (current_file->d_name[0] == '.' && !(opt->opt_a))
				continue;
			PATH_TMP = ft_addpath(CURRENT_PATH, current_file->d_name);
			if (errno != 0)
				ft_error(errno, path, opt);
			if (!root)
				root = ft_create_node(current_file, PATH_TMP, opt);
			else
				ft_place_node(&root, ft_create_node(current_file, PATH_TMP, opt), opt);
			ft_strdel(&PATH_TMP);
		}
		closedir(current_dir);
	}
	if (errno == ENOTDIR)
		return (ft_error2(path, opt));
	ft_display_ls(opt, path, root);
	// printf("path = %s\n", CURRENT_PATH);
	if (opt->opt_R && path->dir_or_file == DIRECTORY)
	{
		path->sub_index = 1;
		ft_recursivels(root, opt, path);
	}
	return (NULL);
}

void ft_lserror(t_opt *opt, t_path *path)
{
	DIR             *current_dir;

	if ((current_dir = opendir(CURRENT_PATH)))
		closedir(current_dir);
	else
		ft_error2(path, opt);
}

void ft_lsfile(t_opt *opt, t_path *path)
{
	t_node *root;
	t_node *node;
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
		else if (!errno)
			spaceat_theend = 1;
		path->index++;
	}
	if (root)
		ft_display_tree(root, opt);
	if (opt->opt_l)
	{
		ft_calc_blocks(0, 1);
		ft_spaceafteruser("", 1);
		ft_spaceaftergroup("", 1);
		ft_spacebeforenlink(0, 1);
		ft_spacebeforenbytes(0, 1);
	}
	if (spaceat_theend && root)
	{
		// ft_putendl("yo");
		ft_putchar('\n');
	}
}
