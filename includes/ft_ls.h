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
}				t_opt;

typedef	struct	s_stat
{
	char		*mode;
	char		*time;
	char		*user;
	char		*group;
	int			nlink;
	char		*name;
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

void	ft_error(int err);

/*
**	OPTION.C
*/

t_opt	*ft_opt(int argc, char **argv, int *i);

/*
**	STAT.C
*/

t_stat	*ft_create_stat(struct dirent *file, const char *path);

/*
**	LS.C
*/

void ft_ls(t_opt *opt, char *path);
char *ft_createpath(char *path, char *to_add);
/*
**	TREE.c
*/

t_node	*ft_create_node(struct dirent *file, const char *path);
void ft_place_node(t_node **root, struct dirent *file, const char *path);
void ft_recursivels(t_node *tree, t_opt *opt, char *path);

/*
**	DISPLAY.c
*/

void ft_display_tree(t_node *tree, t_opt *opt);
void ft_display_file(t_opt *opt, t_node *node);
#endif
