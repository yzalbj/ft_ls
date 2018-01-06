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

void	ft_putcolor4(t_stat *stat, char *lscolor, char *flag)
{
	if (lscolor[0] == 'a' && lscolor[1] == 'd' && stat->mode[5] == 'w'
			&& stat->mode[9] != 't' && stat->mode[0] == 'd')
	{
		ft_putstr(BLACK);
		ft_putstr(BACKGROUND_YELLOW);
		ft_putstr(stat->name);
		*flag = 1;
	}
}

void	ft_putcolor3(t_stat *stat, char *lscolor, char *flag)
{
	if (lscolor[0] == 'a' && lscolor[1] == 'b' && (stat->mode[9] == 't'
		|| stat->mode[9] == 'T') && stat->mode[0] == '-')
	{
		ft_putstr(BLACK);
		ft_putstr(BACKGROUND_RED);
		ft_putstr(stat->name);
		*flag = 1;
	}
	else if (lscolor[0] == 'a' && lscolor[1] == 'g' && stat->mode[9] == 's')
	{
		ft_putstr(BLACK);
		ft_putstr(BACKGROUND_CYAN);
		ft_putstr(stat->name);
		*flag = 1;
	}
	else if (lscolor[0] == 'a' && lscolor[1] == 'c' && stat->mode[5] == 'w'
			&& (stat->mode[9] == 't' || stat->mode[9] == 'T')
			&& stat->mode[0] == 'd')
	{
		ft_putstr(BLACK);
		ft_putstr(BACKGROUND_GREEN);
		ft_putstr(stat->name);
		*flag = 1;
	}
}

void	ft_putcolor2(t_stat *stat, char *lscolor, char *flag)
{
	if (lscolor[0] == 'b' && lscolor[1] == 'x' && (stat->mode[3] == 'x'
			|| stat->mode[6] == 'x' || stat->mode[9] == 'x') &&
			stat->mode[0] == '-')
	{
		ft_putstr(RED);
		ft_putstr(stat->name);
		*flag = 1;
	}
	else if (lscolor[0] == 'e' && lscolor[1] == 'g' && stat->mode[0] == 'b')
	{
		ft_putstr(BLUE);
		ft_putstr(BACKGROUND_CYAN);
		ft_putstr(stat->name);
		*flag = 1;
	}
	else if (lscolor[0] == 'e' && lscolor[1] == 'd' && stat->mode[0] == 'c')
	{
		ft_putstr(BLUE);
		ft_putstr(BACKGROUND_YELLOW);
		ft_putstr(stat->name);
		*flag = 1;
	}
}

void	ft_putcolor1(t_stat *stat, char *lscolor, char *flag)
{
	if (lscolor[0] == 'G' && lscolor[1] == 'x' && stat->mode[0] == 'd')
	{
		ft_putstr(BOLD_CYAN);
		ft_putstr(stat->name);
		*flag = 1;
	}
	else if (lscolor[0] == 'f' && lscolor[1] == 'x' && stat->mode[0] == 'l')
	{
		ft_putstr(MAGENTA);
		ft_putstr(stat->name);
		*flag = 1;
	}
	else if (lscolor[0] == 'c' && lscolor[1] == 'x' && stat->mode[0] == 's')
	{
		ft_putstr(GREEN);
		ft_putstr(stat->name);
		*flag = 1;
	}
	else if (lscolor[0] == 'd' && lscolor[1] == 'x' && stat->mode[0] == 'p')
	{
		ft_putstr(YELLOW);
		ft_putstr(stat->name);
		*flag = 1;
	}
}

void	ft_putcolor(t_stat *stat)
{
	char *lscolor;
	char flag;
	char i;

	lscolor = getenv("LSCOLORS");
	i = ft_strlen(lscolor);
	lscolor = lscolor + i - 2;
	flag = 0;
	while (i && !flag)
	{
		ft_putcolor1(stat, lscolor, &flag);
		ft_putcolor2(stat, lscolor, &flag);
		ft_putcolor3(stat, lscolor, &flag);
		ft_putcolor4(stat, lscolor, &flag);
		ft_putstr(RESET);
		lscolor = lscolor - 2;
		i = i - 2;
	}
	if (!flag)
		ft_putstr(stat->name);
}
