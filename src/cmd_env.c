/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 14:55:03 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/08 14:55:05 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void			cmd_env(char **args)
{
	int			i;

	i = 0;
	if (args && *args)
		if (cmd_exec(args[0], args))
			return ;
	while (g_env[i])
	{
		ft_putendl(g_env[i]);
		i++;
	}
}

int				cmd_resetenv(char *name, char *env)
{
	int			i;
	char		*tmp;

	i = 0;
	while (g_env[i])
	{
		tmp = ft_strsub(g_env[i], 0, ft_strlen(name));
		if (ft_strcmp(name, tmp) == 0)
		{
			free(g_env[i]);
			g_env[i] = ft_strdup(env);
			free(tmp);
			return (1);
		}
		free(tmp);
		i++;
	}
	return (0);
}

void			cmd_setenv(char **envs)
{
	int			i;
	char		*varname;
	char		*tmp;
	int			size;

	i = -1;
	while (envs[++i])
	{
		if (ft_strchr(envs[i], '=') && ft_strlen(envs[i]) > 1)
		{
			varname = var_namecut(envs[i]);
			if (ft_strlen(varname) && (tmp = get_var(varname)))
			{
				cmd_resetenv(varname, envs[i]);
				free(tmp);
			}
			else if (ft_strlen(varname))
			{
				size = ft_elems(g_env);
				g_env = realloc_env(size + 1);
				g_env[size] = ft_strdup(envs[i]);
			}
			free(varname);
		}
	}
}

static int		isthere_changes(char **envs)
{
	int			i;
	int			count;

	count = 0;
	i = 0;
	while (g_env[i])
	{
		if (is_exist(envs, g_env[i]))
			count++;
		i++;
	}
	return (count);
}

void			cmd_unsetenv(char **envs)
{
	char		**new;
	int			size;
	int			i;
	int			j;
	int			elems;

	j = 0;
	i = 0;
	if (!(elems = isthere_changes(envs)))
		return ;
	size = ft_elems(g_env) - elems;
	new = (char**)malloc(sizeof(char*) * (size + 1));
	while (g_env[i])
	{
		if (is_exist(envs, g_env[i]) == 0)
		{
			new[j] = ft_strdup(g_env[i]);
			j++;
		}
		free(g_env[i]);
		i++;
	}
	new[size] = NULL;
	free(g_env);
	g_env = new;
}
