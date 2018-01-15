/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:56:08 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 15:53:44 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	ft_spacefornbytes(t_stat *stat)
{
	char space[2];

	space[0] = ft_spacebeforenbytes(1, 0, 0, 0) - ft_intlen(stat->size[0]);
	space[1] = ft_spacebeforenbytes(1, 0, 0, 1) - ft_intlen(stat->size[1]);
	if (stat->mode[0] != 'c' && stat->mode[0] != 'b' && space[0] > 0)
		ft_putstr("   ");
	while (space[0] > 0 && space[0]--)
		ft_putchar(' ');
	if (stat->mode[0] == 'c' || stat->mode[0] == 'b')
	{
		ft_putnbr(stat->size[0]);
		ft_putstr(", ");
	}
	while (space[1] > 0 && space[1]--)
		ft_putchar(' ');
	ft_putnbr(stat->size[1]);
}

void	ft_displaylong(t_opt *opt, t_stat *stat)
{
	char	space;

	space = ft_spacebeforenlink(1, 0) + 2 - ft_intlen(stat->nlink);
	ft_putstr(stat->mode);
	while (space--)
		ft_putstr(" ");
	ft_putnbr(stat->nlink);
	ft_putstr(" ");
	ft_putstr(stat->user);
	space = ft_spaceafteruser("", 0) + 2 - ft_strlen(stat->user);
	while (space--)
		ft_putstr(" ");
	ft_putstr(stat->group);
	space = ft_spaceaftergroup("", 0) + 2 - ft_strlen(stat->group);
	while (space--)
		ft_putstr(" ");
	ft_spacefornbytes(stat);
	ft_display_time(opt, stat);
}

void	ft_display_file(t_opt *opt, t_stat *stat)
{
	if (opt->opt_l)
		ft_displaylong(opt, stat);
	if (!opt->opt_upperg)
		ft_putstr(stat->name);
	else
		ft_putcolor(stat);
	if (stat->mode[0] == 'l' && opt->opt_l)
	{
		ft_putstr(" -> ");
		ft_putstr(stat->readlink);
	}
	ft_putchar('\n');
}

void	ft_display_tree(t_node *tree, t_opt *opt)
{
	if (!tree)
		return ;
	if (!opt->opt_1 && !opt->opt_l)
		ft_columns(tree, opt);
	else
	{
		if (!opt->opt_r && tree->left)
			ft_display_tree(tree->left, opt);
		else if (opt->opt_r && tree->right)
			ft_display_tree(tree->right, opt);
		ft_display_file(opt, tree->stat);
		if (!opt->opt_r && tree->right)
			ft_display_tree(tree->right, opt);
		else if (opt->opt_r && tree->left)
			ft_display_tree(tree->left, opt);
	}
}

void	ft_display_ls(t_opt *opt, t_path *path, t_node *root)
{
	if ((!errno || errno == EACCES) && CURRENT_PATH
		&& path->dir_or_file == DIRECTORY &&
			(path->argc - 1 - opt->opt_nb > 1 || path->sub_index))
	{
		if (path->sub_index || (!root && path->sub_index))
			ft_putchar('\n');
		ft_printwithoutslash(CURRENT_PATH);
		ft_putstr(":\n");
	}
	if (errno != 0)
		ft_error(errno, path, opt);
	else
	{
		if (opt->opt_l && root && root->stat->mode[0] != 'l')
		{
			ft_putstr("total ");
			ft_putnbr(ft_calc_blocks(0, 1));
			ft_putchar('\n');
		}
		path->sub_index++;
		ft_display_tree(root, opt);
		if (opt->opt_l)
			ft_resetspaces();
	}
}
