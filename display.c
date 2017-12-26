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

void ft_display_time(t_opt *opt, t_stat *stat)
{
    char *copy_time;
    time_t current;

    if (!opt->opt_T)
    {
        if (stat->epoch_sec > time(&current) - 15780000 &&
			stat->epoch_sec <= time(&current))
            ft_putstr(ft_strsub(stat->time, 0, 12));
        else
        {
            // c cheum
            copy_time = ft_strndup(stat->time, 6);
            ft_putstr(copy_time);
            ft_putstr("  ");
            ft_putstr(ft_strsub(stat->time, 16, 4));
        }
    }
    else
        ft_putstr(stat->time);
}

void ft_displaylong(t_opt *opt, t_stat *stat)
{
    char    space;

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
        space = ft_spaceaftergroup("", 0) + 2- ft_strlen(stat->group);
        while (space--)
            ft_putstr(" ");
    //espace entre group et size pas bon --> ./ft_ls -l /dev
       space = ft_spacebeforenbytes(1, 0) - ft_intlen(stat->size[0]);
       while (space--)
           ft_putstr(" ");
		if (stat->mode[0] == 'c' || stat->mode[0] == 'b')
		{
			ft_putnbr(stat->size[0]);
			ft_putstr(",   ");
			ft_putnbr(stat->size[1]);
		}
		else
        	ft_putnbr(stat->size[0]);
        ft_putstr(" ");
        ft_display_time(opt, stat);
        ft_putstr(" ");
}

void ft_display_file(t_opt *opt, t_stat *stat)
{
    if (opt->opt_l)
        ft_displaylong(opt, stat);
    ft_putstr(stat->name);
	// printf(" --> epoch == %ld\n", stat->epoch);
    if (stat->mode[0] == 'l' && opt->opt_l)
    {
        ft_putstr(" -> ");
        ft_putstr(stat->readlink);
    }
    ft_putchar('\n');
}

void ft_display_tree(t_node *tree, t_opt *opt)
{
    if (!tree)
        return ;
    if (!opt->opt_r && tree->left)
        ft_display_tree(tree->left, opt);
    else if(opt->opt_r && tree->right)
        ft_display_tree(tree->right, opt);
    ft_display_file(opt, tree->stat);
    if (!opt->opt_r && tree->right)
        ft_display_tree(tree->right, opt);
    else if(opt->opt_r && tree->left)
        ft_display_tree(tree->left, opt);
}
