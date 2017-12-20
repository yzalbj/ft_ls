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
# include <errno.h>

# define FALSE_OPT -1

typedef	struct	s_opt
{
	char opt_l;
	char opt_r;
	char opt_a;
	char opt_R;
	char opt_t;
	char opt_T;
	char opt_nb;
}				t_opt;

typedef	struct	s_stat
{
	char		*mode;
	char		*time;
	time_t		epoch;
	char		*user;
	char		*group;
	int			nlink;
	int			size[2];
	char		*name;
	char		*readlink;
	// struct stat	*all_stat;
}				t_stat;

typedef	struct	s_node
{
	t_stat			*stat;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;


void print2D(t_node *root);
/*
**	ERROR.C
*/

void	ft_error(int err, char *path, t_opt *opt);

/*
**	OPTION.C
*/

t_opt	*ft_opt(int argc, char **argv, int *i);

/*
**	STAT.C
*/

t_stat	*ft_create_stat(struct dirent *file, char *path, t_opt *opt);

/*
**	CALC_SPACE.C
*/

char	ft_spacebeforenlink(int nlink, int reset);
char	ft_spacebeforenbytes(int size, int reset);
int		ft_calc_blocks(int blocks, int reset);
int     ft_spaceafteruser(char  *user, int reset);
int     ft_spaceaftergroup(char  *group, int reset);

/*
**	LS.C
*/

void ft_ls(t_opt *opt, char *path, int argc);
char *ft_createpath(char *path, char *to_add);
char *ft_removeslash(char *path);
char *ft_lastfile(char * path);
/*
**	TREE.c
*/

t_node	*ft_create_node(struct dirent *file, char *path, t_opt *opt);
void ft_place_node(t_node **root, t_node *node, t_opt *opt);
void ft_recursivels(t_node *tree, t_opt *opt, char *path, int argc);

/*
**	DISPLAY.c
*/

void ft_display_tree(t_node *tree, t_opt *opt);
void ft_display_file(t_opt *opt, t_stat *stat);
#endif
