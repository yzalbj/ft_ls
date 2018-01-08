/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 16:54:05 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/06 18:42:25 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	ft_putcolor4(t_stat *stat, char *flag)
{
	if (stat->mode[5] == 'w' && stat->mode[9] != 't' && stat->mode[0] == 'd')
	{
		ft_putstr(BLACK);
		ft_putstr(BACKGROUND_YELLOW);
		*flag = 1;
	}
}

void	ft_putcolor3(t_stat *stat, char *flag)
{
	if ((stat->mode[9] == 't' || stat->mode[9] == 'T') && stat->mode[0] == '-')
	{
		ft_putstr(BLACK);
		ft_putstr(BACKGROUND_RED);
		*flag = 1;
	}
	else if (stat->mode[9] == 's')
	{
		ft_putstr(BLACK);
		ft_putstr(BACKGROUND_CYAN);
		*flag = 1;
	}
	else if (stat->mode[5] == 'w' && (stat->mode[9] == 't' ||
		stat->mode[9] == 'T') && stat->mode[0] == 'd')
	{
		ft_putstr(BLACK);
		ft_putstr(BACKGROUND_GREEN);
		*flag = 1;
	}
}

void	ft_putcolor2(t_stat *stat, char *flag)
{
	if ((stat->mode[3] == 'x' || stat->mode[6] == 'x' || stat->mode[9] == 'x')
		&& stat->mode[0] == '-')
	{
		ft_putstr(RED);
		*flag = 1;
	}
	else if (stat->mode[0] == 'b')
	{
		ft_putstr(BLUE);
		ft_putstr(BACKGROUND_CYAN);
		*flag = 1;
	}
	else if (stat->mode[0] == 'c')
	{
		ft_putstr(BLUE);
		ft_putstr(BACKGROUND_YELLOW);
		*flag = 1;
	}
}

void	ft_putcolor1(t_stat *stat, char *flag)
{
	if (stat->mode[0] == 'd')
	{
		ft_putstr(BOLD_CYAN);
		*flag = 1;
	}
	else if (stat->mode[0] == 'l')
	{
		ft_putstr(MAGENTA);
		*flag = 1;
	}
	else if (stat->mode[0] == 's')
	{
		ft_putstr(GREEN);
		*flag = 1;
	}
	else if (stat->mode[0] == 'p')
	{
		ft_putstr(YELLOW);
		*flag = 1;
	}
}

void	ft_putcolor(t_stat *stat)
{
	char flag;

	flag = 0;
	if (!flag)
		ft_putcolor4(stat, &flag);
	if (!flag)
		ft_putcolor3(stat, &flag);
	if (!flag)
		ft_putcolor2(stat, &flag);
	if (!flag)
		ft_putcolor1(stat, &flag);
	ft_putstr(stat->name);
	ft_putstr(RESET);
}
