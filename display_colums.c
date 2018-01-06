/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_colums.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:12:06 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/05 16:36:48 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

int ft_nbandsize_elem(t_node *tree, int flag)
{
	static size_t	nb_elem;
	static int		size_elem;

	if (tree)
	{
		// ft_putnbr(nb_elem);
		// ft_putchar('\n');
		if (size_elem < (int)ft_strlen(tree->stat->name))
			size_elem = (int)ft_strlen(tree->stat->name);
		nb_elem++;
	}
	if (!flag)
		return (size_elem);
	return (nb_elem);
}

void ft_display_columsright(t_node *tree, t_col *col, t_opt *opt)
{
	if (!tree || (!tree->left && !tree->right))
		return ;
	while (col->tmp_col < col->column)
	{
		if (!col->tmp_elem)
		{
			ft_display_file(opt, tree->stat);
			col->tmp_elem = col->elempercol;
		}
		else if (col->tmp_elem > 0)
		{
			col->tmp_elem--;
			if (tree->left && !tree->left->left && !tree->left->right)
				ft_display_columsright(tree->right, col, opt);
			else if (tree->left)
				ft_display_columsright(tree->left, col, opt);
			else if (tree->right)
				ft_display_columsright(tree->right, col, opt);
		}
		// ft_putendl("=======================");
		// ft_putendl(tree->stat->name);
		col->tmp_col++;
	}
	// ft_putendl("en dessous la buoucle");
}

void ft_display_columsleft(t_node *tree, t_col *col, int flag, t_opt *opt)
{
	if (tree->left)
	{
		ft_putendl("enter the tree->left");
		ft_display_columsleft(tree->left, col, 0, opt);
	}
	while (col->tmp_col < col->column)
	{
		ft_display_file(opt, tree->stat);
		col->tmp_elem = col->elempercol;
		while (col->tmp_elem)
		{
			col->tmp_elem--;
			if (flag)
				ft_display_columsright(tree->right, col, opt);
			return ;
		}
		col->tmp_col++;
	}
}

void ft_columns(t_node *tree, t_opt *opt)
{
	struct	winsize w;
	t_col	col;
	int		maxlen;

	ioctl(0, TIOCGWINSZ, &w);
	// col.column = (int)w.ws_col / 20 > 0 ? (int)w.ws_col / 20 : 1;
	printf ("lines %d\n", w.ws_row);
	printf ("columns %d\n", w.ws_col);
	maxlen = ft_nbandsize_elem(NULL, 0) + 4;
	col.column = (int)w.ws_col / maxlen > 0 ? (int)w.ws_col / maxlen : (int)w.ws_col / maxlen ;
	col.tmp_col = 0;
	col.elempercol = (ft_nbandsize_elem(NULL, 1) + 1) / col.column;
	if ((ft_nbandsize_elem(NULL, 1) + 1) / col.column > 0)
		col.elempercol++;
	ft_putnbr(col.elempercol);
	ft_putendl("\n====");
	ft_putnbr(col.column);
	ft_putendl("\n====");
	ft_putnbr(ft_nbandsize_elem(NULL, 1) + 1);
	ft_putendl("\n====");
	ft_display_columsleft(tree, &col, 1, opt);
}
