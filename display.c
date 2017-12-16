/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:56:08 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/15 13:56:10 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void ft_display_file(t_opt *opt, t_node *node)
{
    if (opt->opt_l)
    {
        ft_putstr(node->stat->mode);
        ft_putstr("  nlink_afaire ");
        ft_putstr(node->stat->user);
        ft_putstr("  ");
        ft_putstr(node->stat->group);
        ft_putstr("  nbytes_afaire ");
        ft_putstr(node->stat->time);
        ft_putstr(" ");
    }
        ft_putendl(node->stat->name);
}
void ft_display_tree(t_node *tree, t_opt *opt)
{
    if (!tree)
        return ;
    if (!opt->opt_r && tree->left)
        ft_display_tree(tree->left, opt);
    else if(opt->opt_r && tree->right)
        ft_display_tree(tree->right, opt);
    ft_display_file(opt, tree);
    if (!opt->opt_r && tree->right)
        ft_display_tree(tree->right, opt);
    else if(opt->opt_r && tree->left)
        ft_display_tree(tree->left, opt);
}
