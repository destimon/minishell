/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 09:19:01 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/13 09:20:08 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char			**g_get_env(void)
{
	extern char	**environ;
	char		**en;
	int			i;
	int			len;

	i = 0;
	len = ft_elems(environ);
	if (!(en = (char**)malloc((sizeof(char*) * len + 1))))
		return (NULL);
	while (environ[i])
	{
		en[i] = ft_strdup(environ[i]);
		i++;
	}
	en[i] = NULL;
	return (en);
}

void			g_free_env(void)
{
	int			i;

	i = 0;
	if (!g_env)
		return ;
	while (g_env[i])
	{
		free(g_env[i]);
		i++;
	}
	free(g_env);
}

void			show_prompt(void)
{
	char		*user;
	char		*path;
	char		tmp[PATH_MAX];

	user = get_var("USER");
	if (((getcwd(tmp, PATH_MAX))) != NULL)
	{
		ft_putstr(ANSI_BOLD_GREEN);
		ft_putstr(user);
		free(user);
		ft_putstr(":");
		ft_putstr(ANSI_COLOR_BLUE);
		path = path_homecut(tmp);
		ft_putstr(path);
		free(path);
		ft_putstr(ANSI_BOLD_WHITE);
		ft_putstr("$> ");
		ft_putstr(ANSI_COLOR_RESET);
	}
}

char			*get_path(void)
{
	char		path[PATH_MAX];
	char		*path_ptr;
	char		*slash;

	if ((path_ptr = (getcwd(path, PATH_MAX))) != NULL)
	{
		slash = ft_strdup("/");
		path_ptr = ft_strjoin(path_ptr, slash);
		free(slash);
		return (path_ptr);
	}
	return (NULL);
}

char			**get_envpaths(char *bin)
{
	char		**paths;
	int			i;
	char		*index;
	char		*tmp;
	int			check;

	check = 0;
	i = -1;
	check = search_env(&i);
	if (check == 0)
		return (NULL);
	tmp = ft_strchr(g_env[i], '/');
	if (!(paths = ft_strsplit(ft_strchr(g_env[i], '/'), ':')))
		paths = ft_strsplit(g_env[i], ':');
	i = -1;
	while (paths && paths[++i])
	{
		index = paths[i];
		paths[i] = ft_strjoin_free(paths[i], "/", 0, 1);
		free(index);
		index = paths[i];
		paths[i] = ft_strjoin(paths[i], bin);
		free(index);
	}
	return (paths);
}
