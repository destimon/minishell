/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmanage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 11:55:03 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/11 11:55:06 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char			**realloc_env(size_t size)
{
	char		**new;
	int			i;

	i = 0;
	new = (char**)malloc(sizeof(char*) * (size + 1));
	while (g_env[i])
	{
		new[i] = ft_strdup(g_env[i]);
		free(g_env[i]);
		i++;
	}
	while (i < (int)size)
	{
		new[i] = NULL;
		i++;
	}
	new[size] = NULL;
	free(g_env);
	g_env = new;
	return (new);
}

int				is_exist(char **todel, char *env)
{
	char		*cut;
	int			i;

	cut = var_namecut(env);
	i = 0;
	while (todel[i])
	{
		if (ft_strcmp(todel[i], cut) == 0)
		{
			free(cut);
			return (1);
		}
		i++;
	}
	free(cut);
	return (0);
}
