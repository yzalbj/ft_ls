/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:04:29 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 16:22:02 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	ft_free_node(t_node **root, t_opt *opt)
{
	if ((*root)->stat)
	{
		free((*root)->stat->name);
		(*root)->stat->name = NULL;
		if (opt->opt_l)
		{
			ft_strdel(&(*root)->stat->user);
			ft_strdel(&(*root)->stat->group);
			if ((*root)->stat->mode[0] == 'l')
				ft_strdel(&(*root)->stat->readlink);
		}
		ft_strdel(&(*root)->stat->year);
		ft_strdel(&(*root)->stat->time);
		ft_strdel(&(*root)->stat->mode);
		free((*root)->stat);
		(*root)->stat = NULL;
	}
	free((*root));
	(*root) = NULL;
}

void	ft_free_tree(t_node **tree, t_opt *opt)
{
	if ((*tree) && (*tree)->left)
		ft_free_tree(&(*tree)->left, opt);
	if ((*tree) && (*tree)->right)
		ft_free_tree(&(*tree)->right, opt);
	if ((*tree) && !((*tree)->left) && !((*tree)->right))
		ft_free_node(tree, opt);
}

void	ft_freetab(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		ft_strdel(&(*tab)[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void	ft_freepath(t_path **path)
{
	ft_freetab(&(*path)->all_path);
	free((*path)->path_tmp);
	(*path)->path_tmp = NULL;
	free((*path)->error);
	(*path)->error = NULL;
	free((*path));
	*path = NULL;
}
