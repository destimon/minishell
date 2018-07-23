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

char			*get_var(char *var)
{
	char		*user;
	char		*tmp;
	char		*vname;
	char		*tmpvar;
	int			i;

	i = 0;
	if (!var)
		return (NULL);
	while (g_env[i])
	{
		tmpvar = ft_strdup(g_env[i]);
		vname = ft_strsub(tmpvar, 0, ft_occpos(tmpvar, '='));
		free(tmpvar);
		if (ft_strcmp(var, vname) == 0)
		{
			user = ft_strchr(g_env[i], '=');
			tmp = ft_strdup(user + 1);
			free(vname);
			return (tmp);
		}
		free(vname);
		i++;
	}
	return (NULL);
}

void			set_var(char *name, char *var)
{
	char		*env;
	int			i;

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
	char		*new;
	char		*tmp;
	int			i;
	int			occ;

	i = -1;
	occ = 0;
	if (!path)
		return (NULL);
	while (path[++i])
	{
		if (path[i] == '/')
			occ++;
		if (occ == 3)
			break ;
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

void			help_out(void)
{
	ft_putstr(ANSI_BOLD_GREEN);
	ft_putendl("#\t>>> Minishell 42 <<<");
	ft_putendl("#");
	ft_putstr(ANSI_BOLD_WHITE);
	ft_putstr("#\techo [arg ...]\n#\tenv [utility [argument ...]]\n#\t");
	ft_putstr("setenv [name[=value] ...]\n#\tunsetenv [name ...]\n#\t");
	ft_putstr("cd [arg ...]\n#\texit\n#\n");
	ft_putstr(ANSI_COLOR_RED);
	ft_putstr("#\tAuteur: dcherend\n");
	ft_putstr(ANSI_COLOR_GREEN);
	ft_putendl("#\n#\t>>> Minishell 42 <<<");
	ft_putstr(ANSI_COLOR_RESET);
}

char			*var_namecut(char *var)
{
	char		*name;

	if ((name = ft_strdupch(var, '=')))
	{
		return (name);
	}
	return (NULL);
}
