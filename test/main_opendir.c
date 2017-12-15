/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 10:45:47 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/14 19:23:23 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

int		main(int argc, char **argv)
{
	DIR				*directory;
	struct dirent 	*sub_dir;
	if (argc != 2)
		return (1);

	directory = opendir(argv[1]);
	perror(strerror(errno));	
	if (!directory)
	{
		ft_putendl("Directory cannot be open");
		return (0);
	}
	while ((sub_dir = readdir(directory)))
		ft_putendl(sub_dir->d_name);
	if ((closedir(directory)))
		ft_putendl("Error when closing the directory");
	return (0);
}
