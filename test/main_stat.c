/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_stat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:52:56 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/14 18:53:56 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <sys/xattr.h>

void	ft_printoct(int *oct, int len)
{
	while (len >=0)
	{
		ft_putnbr(oct[len]);
		len--;
	}
	ft_putchar('\n');
}

char	*ft_findtype(mode_t st_mode, char *mode)
{
	int		len;
	int		*oct;

	len = 0;
	oct = ft_dectooct(st_mode);
	while (oct[len + 1] != -1)
		len++;
	if (len == 5 && oct[len] == 1 && oct[len - 1] == 0 && oct[len - 2] == 0)
		mode[0] = '-';
	else if (oct[len] == 1 && oct[len - 1] == 2 && oct[len - 2] == 0)
		mode[0] = 'l';
	else if (oct[len] == 1 && oct[len - 1] == 4 && oct[len - 2] == 0)
		mode[0] = 's';
	else if (oct[len] == 1 && oct[len - 1] == 6 && oct[len - 2] == 0)
		mode[0] = 'w';
	else if (oct[len] == 1 && oct[len - 1] == 0)
		mode[0] = 'p';
	else if (oct[len] == 2 && oct[len - 1] == 0)
		mode[0] = 'c';
	else if (oct[len] == 4 && oct[len - 1] == 0)
		mode[0] = 'd';
	else if (oct[len] == 6 && oct[len - 1] == 0)
		mode[0] = 'b';
	return (mode);
}

char	*ft_findmode(mode_t st_mode)
{
	int		*binary;
	char	*mode;
	int		len;
	int		tmp;

	binary = ft_dectobin(st_mode);
	mode = ft_strnew(10);
	len = 0;
	tmp = 8;
	while (tmp >= 0)
	{
		if (binary[len++] == 1)
		{
			if (tmp % 3 == 2)
				mode[tmp + 1] = 'x';
			if (tmp % 3 == 1)
				mode[tmp + 1] = 'w';
			if (tmp % 3 == 0)
				mode[tmp + 1] = 'r';
		}
		else
			mode[tmp + 1] = '-';
		tmp--;
	}
	ft_findtype(st_mode, mode);
	return (mode);
}

int		main(int argc, char **argv)
{
	struct stat		*file;
	struct group	*groupe;
	struct passwd	*user;
	time_t			temps;
	char			*temps1;
	size_t			content_link;
	char			*buf;
	char			*mode;
	char			*bufxattr;
	size_t			nbr_xattr;

	buf = ft_strnew(4095);
	bufxattr = ft_strnew(4095);
	if (argc != 2)
		return (0);
	file = (struct stat *)malloc(sizeof(struct stat));
	if ((lstat(argv[1], file)))
	{
		ft_putendl("Error when using stat() ;");
		return (0);
	}
	groupe = getgrgid(file->st_gid);
	user = getpwuid(file->st_uid);
	if (file && user && groupe)
	{
		mode = ft_findmode(file->st_mode);
		ft_putstr(mode);
		ft_putstr("  ");
		ft_putnbr(file->st_nlink);
		ft_putchar(' ');
		ft_putstr(user->pw_name);
		ft_putstr("  ");
		ft_putstr(groupe->gr_name);
		ft_putstr("  ");
		ft_putnbr(file->st_size);
		ft_putchar(' ');
		temps = time(&file->st_atimespec.tv_sec);
		temps1 = ft_strsub(ctime(&temps), 4, 12);
		ft_putstr(temps1);
		ft_putchar(' ');
		ft_putendl(argv[1]);
		/*if (mode[0] == 'l')
		{
			ft_putstr("content of symbolic link = ");
			content_link = readlink(argv[1], buf, 4096);
			ft_putnbr(content_link);
			ft_putchar('\n');
		}
		nbr_xattr = listxattr(argv[1], bufxattr, 4095);
		ft_putendl(bufxattr);
		ft_putnbr(nbr_xattr);
		ft_putchar('\n');*/
	}
	return (0);
}
