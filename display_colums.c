/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_colums.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:12:06 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/08 18:24:51 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

int		ft_nbandsize_elem(t_node *tree, int flag, int reset)
{
	static size_t	nb_elem;
	static int		size_elem;

	if (tree)
	{
		if (size_elem < (int)ft_strlen(tree->stat->name))
			size_elem = (int)ft_strlen(tree->stat->name);
		nb_elem++;
	}
	if (reset)
	{
		nb_elem = 0;
		size_elem = 0;
	}
	if (!flag)
		return (size_elem);
	return (nb_elem);
}

void	ft_filltab(t_node *tree, t_stat *tab, int *index, t_opt *opt)
{
	if (!tree)
		return ;
	if (!opt->opt_r && tree->left)
		ft_filltab(tree->left, tab, index, opt);
	else if (opt->opt_r && tree->right)
		ft_filltab(tree->right, tab, index, opt);
	tab[*index].name = ft_strdup(tree->stat->name);
	tab[*index].mode = ft_strdup(tree->stat->mode);
	(*index)++;
	if (!opt->opt_r && tree->right)
		ft_filltab(tree->right, tab, index, opt);
	else if (opt->opt_r && tree->left)
		ft_filltab(tree->left, tab, index, opt);
}

/*
**	i[0] == index pour la ligne actuelle
**	i[1] == index pour le numero d'elements auquel on est
**	i[2] == index pour le nombre d'espace a afficher apres le name
*/

void	ft_displaytab(t_stat *tab, t_col *col, t_opt *opt)
{
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (i[0] < col->elempercol)
	{
		i[1] = i[0];
		while (i[1] < col->nb_elem)
		{
			i[2] = col->maxlen - ft_strlen(tab[i[1]].name) + 1;
			if (!opt->opt_upperg)
				ft_putstr(tab[i[1]].name);
			else if (opt->opt_upperg)
				ft_putcolor(&tab[i[1]]);
			while (i[2] > 0 && i[2]--)
				ft_putchar(' ');
			i[1] += col->elempercol;
		}
		i[0]++;
		ft_putchar('\n');
	}
}

void	ft_createtab(t_node *tree, t_col *col, t_opt *opt)
{
	t_stat		*tab;
	int			i;

	i = 0;
	if (!(tab = (t_stat *)malloc(sizeof(t_stat) * (col->nb_elem + 1))))
		return ;
	ft_filltab(tree, tab, &i, opt);
	ft_displaytab(tab, col, opt);
	i = 0;
	while (i < col->nb_elem)
	{
		ft_strdel(&tab[i].name);
		ft_strdel(&tab[i].mode);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_columns(t_node *tree, t_opt *opt)
{
	struct winsize	w;
	t_col			col;

	ioctl(0, TIOCGWINSZ, &w);
	col.nb_elem = ft_nbandsize_elem(NULL, 1, 0) + 1;
	if (col.nb_elem == 1 && !tree)
		return ;
	col.maxlen = ft_nbandsize_elem(NULL, 0, 0) + 1;
	col.column = (int)w.ws_col / col.maxlen;
	col.tmp_col = 0;
	if (col.column > col.nb_elem)
		col.elempercol = col.column / col.nb_elem;
	else
		col.elempercol = col.nb_elem / col.column;
	if (col.nb_elem / col.column > 0)
		col.elempercol++;
	if (col.nb_elem < col.column)
		col.elempercol = 1;
	ft_createtab(tree, &col, opt);
	ft_nbandsize_elem(NULL, 1, 1);
}
