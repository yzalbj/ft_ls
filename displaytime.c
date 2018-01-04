/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 15:54:07 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/04 15:55:23 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	ft_display_opt_uppert(t_stat *stat)
{
	time_t	current;
	char	*str_time;

	if (stat->epoch_sec > time(&current) - 15780000 &&
		stat->epoch_sec <= time(&current))
	{
		str_time = ft_strsub(stat->time, 0, 12);
		ft_putstr(str_time);
		ft_strdel(&str_time);
	}
	else
	{
		str_time = ft_strsub(stat->time, 0, 6);
		ft_putstr(str_time);
		ft_strdel(&str_time);
		ft_putstr("  ");
		ft_putstr(stat->year);
	}
}

void	ft_display_time(t_opt *opt, t_stat *stat)
{
	ft_putchar(' ');
	if (!opt->opt_T)
		ft_display_opt_uppert(stat);
	else
	{
		ft_putstr(stat->time);
		ft_putstr(stat->year);
	}
	ft_putchar(' ');
}
