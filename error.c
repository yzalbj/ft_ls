/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:29:27 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/14 15:57:04 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_ls.h"

void	ft_error(int err, char *path, t_opt *opt)
{
	t_stat	*stat;

	if (err == FALSE_OPT)
		ft_putendl_fd("usage: ft_ls [-RTalrt] [file ...]", 2);
	if (errno == EACCES)
    {
        ft_putstr("ft_ls: ");
        ft_putstr(ft_lastfile(path));
        ft_putendl(": Permission denied\n");
    }
    else if (errno == ENOTDIR)
	{
		stat = ft_create_stat(NULL, path, opt);
		if (stat->mode[0] == 'd')
			//skip les dossiers pour faire que les fichiers puis les dossier quand on fait un ls -l *
        ft_display_file(opt, stat);
	}
    else if (errno == ENOENT)
    {
        ft_putstr("ft_ls: ");
        ft_putstr(path);
       ft_putendl(": No such file or directory");
    }
	errno = 0;
}
