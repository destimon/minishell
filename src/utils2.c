/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:06:19 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/10 15:06:21 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char 			*get_var(char *var)
{
	char 		*user;
	char 		*tmp;
	int 		i;

	i = 0;
	if (!var)
		return (NULL);
	while (g_env[i])
	{
		if (ft_strstr(g_env[i], var))
		{
			user = ft_strchr(g_env[i], '=');
			tmp = ft_strdup(user + 1);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

void			*set_var(char *name, char *var)
{
	char 		*env;
	char 		*nvar;
	int 		i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strstr(g_env[i], name))
		{
			env = ft_strjoin(name, var);
			free(g_env[i]);
			g_env[i] = env;
		}
		i++;
	}
}

char			*path_homecut(char *path)
{
	char 		*new;
	char 		*tmp;
	int 		i;
	int 		occ;

	i = 0;
	occ = 0;
	if (path)
	{
		while (path[i])
		{
			if (path[i] == '/')
				occ++;
			if (occ == 3)
				break;
			i++;
		}
		if (occ >= 2)
		{
			tmp = ft_strdup(&path[i]);
			new = ft_strjoin_free("~", tmp, 1, 0);
			free(tmp);
			return (new);
		}
		else
			return (ft_strdup(path));
	}
	return (NULL);
}

char				*var_namecut(char *var)
{
	char 			*name;

	if ((name = ft_strdupch(var, '=')))
	{
		return (name);
	}
	return (NULL);
}