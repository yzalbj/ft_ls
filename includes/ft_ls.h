/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 12:08:28 by jblazy            #+#    #+#             */
/*   Updated: 2017/12/14 16:33:27 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H

# include "../libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <sys/xattr.h>
# include <stdio.h>

# define FALSE_OPT -1

typedef	struct	s_opt
{
	char opt_l;
	char opt_r;
	char opt_a;
	char opt_R;
	char opt_t;
}				t_opt;

typedef	struct	s_stat
{
	char		*mode;
	char		*time;
	struct stat	*all_stat;
}				t_stat;

typedef	struct	s_node
{
	struct s_node	*left;
	struct s_node	*right;
	struct s_node	*pater;
	t_stat			*stat;
}					t_node;


/*
**	ERROR.C
*/

void	ft_error(int err);

/*
**	OPTION.C
*/

t_opt	*ft_opt(int argc, char **argv, int *i);

/*
**	STAT.C
*/

t_stat	*ft_create_stat(struct dirent *file);
#endif
