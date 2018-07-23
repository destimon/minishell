/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 16:30:02 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/12 16:30:05 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void		cd_home(void)
{
	char		*user;
	char		*tmp;

	user = get_var("HOME");
	tmp = getcwd(NULL, PATH_MAX);
	set_var("OLDPWD=", tmp);
	free(tmp);
	chdir(user);
	free(user);
}

static void		cd_home2(char *path)
{
	char		*new;
	char		*home;

	home = get_var("HOME");
	if (!home)
	{
		ft_putendl("Set HOME variable back, alo!");
		return ;
	}
	new = ft_strchr(path, '/');
	if (new)
	{
		new = ft_strjoin(home, new);
		free(home);
		free(new);
	}
	else
	{
		new = home;
		free(new);
	}
	if ((chdir(new)) == -1)
		return (cd_errors(ERR_CD_UNEXIST));
}

static void		cd_minus(void)
{
	char		*user;
	char		*tmp;
	char		*msg;

	tmp = getcwd(NULL, PATH_MAX);
	user = get_var("OLDPWD");
	if (!user)
	{
		if (tmp)
			free(tmp);
		ft_putendl("Set OLDPWD variable back, alo!");
		return ;
	}
	chdir(user);
	msg = path_homecut(user);
	if (access(user, F_OK) == 0)
		ft_putendl(msg);
	set_var("OLDPWD=", tmp);
	free(user);
	if (msg)
		free(msg);
	free(tmp);
}

void			cmd_cd(char **dirs)
{
	char		*tmp;

	if (!dirs[0])
		cd_home();
	else if (ft_elems(dirs) > 1)
		return (cd_errors(ERR_CD_MANYARGS));
	else if (dirs[0][0] == '~')
		cd_home2(dirs[0]);
	else if (ft_elems(dirs) == 0 || ft_strcmp(dirs[0], "--") == 0)
		cd_home();
	else if (ft_strcmp(dirs[0], "-") == 0)
		cd_minus();
	else
	{
		tmp = getcwd(NULL, PATH_MAX);
		set_var("OLDPWD=", tmp);
		free(tmp);
		if ((access(dirs[0], F_OK)) != 0)
			return (cd_errors(ERR_CD_UNEXIST));
		if ((access(dirs[0], R_OK)) != 0)
			return (cd_errors(ERR_CD_UNACCESS));
		if ((chdir(dirs[0])) == -1)
			return (cd_errors(ERR_CD_UNEXIST));
	}
}
