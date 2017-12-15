/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:01:27 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/14 16:33:19 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

int		main(int argc, char **argv)
{
		t_opt	*opt;
		int		i;

		i = 1;
		opt = ft_opt(argc, argv, &i);
		if (argc == 1)
					ft_ls(opt, ".");
		else
		{
			while (i < argc)
			{
				ft_ls(opt, argv[i])
				i++;
			}
		}
		//		printf("opt_l = %d\nopt_r = %d\nopt_a = %d\nopt_R = %d\nopt_t = %d\n",
			//	opt->opt_l, opt->opt_r, opt->opt_a, opt->opt_R, opt->opt_t);
	return (0);
}
