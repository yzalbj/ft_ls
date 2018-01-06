/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 19:19:10 by jblazy            #+#    #+#             */
/*   Updated: 2018/01/06 19:19:14 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

int  ft_major(dev_t _x)
{
        return ((_x >> 24) & 0xff);
}

int  ft_minor(dev_t _x)
{
        return ((_x) & 0xffffff);
}
