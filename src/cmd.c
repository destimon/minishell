/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 10:45:19 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/08 10:45:23 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 * Fix echo o "$PATH"
 */

void			cmd_echo(char **strings)
{
	char 		*var;
	int 		i;
	_Bool		endl;

	endl = 0;
	if (!strings)
		return ;
	i = -1;
	while (strings[++i])
	{
		if (endl)
			ft_putstr(" ");
		if (strings[i][0] == '$' && ft_strlen(strings[i]) > 1)
		{
			if ((var = get_var(&strings[i][1])))
			{
				ft_puts_except(var, '\"');
				free(var);
				endl = 1;
			}
		}
		else if (strings[i][0] == '~')
		{
			if ((var = get_var("HOME=")))
				ft_puts_except(var, '\"');
			free(var);
			endl = 1;
		}
		else
		{
			ft_puts_except(strings[i], '\"');
			endl = 1;
		}
	}
	ft_putendl("");
}

void			cmd_cd(char **dirs)
{
	char		*user;
	char		*tmp;
	char 		*msg;

	if (ft_elems(dirs) > 1)
		return (cd_errors(ERR_CD_MANYARGS));
	else if (ft_elems(dirs) == 0 || ft_strcmp(dirs[0], "~") == 0 ||
		ft_strcmp(dirs[0], "--") == 0)
	{
		user = get_var("HOME=");
		tmp = getcwd(NULL, PATH_MAX);
		set_var("OLDPWD=", tmp);
		free(tmp);
		chdir(user);
		free(user);
	}
	else if (ft_strcmp(dirs[0], "-") == 0)
	{
		tmp = getcwd(NULL, PATH_MAX);
		user = get_var("OLDPWD=");
		chdir(user);
		msg = path_homecut(user);
		ft_putendl(msg);
		set_var("OLDPWD=", tmp);
		free(user);
		if (msg)
			free(msg);
		free(tmp);
	}
	else
	{
		tmp = getcwd(NULL, PATH_MAX);
		set_var("OLDPWD=", tmp);
		free(tmp);
		if((access(dirs[0], F_OK)) != 0)
			return (cd_errors(ERR_CD_UNEXIST));
		if ((access(dirs[0], R_OK)) != 0)
			return (cd_errors(ERR_CD_UNACCESS));
		if ((chdir(dirs[0])) == -1)
			return (cd_errors(ERR_CD_UNEXIST));
	}
}

static int		cmd_exec_woenv(char *bin, char **args)
{
	int 		status;
	pid_t		child_pid;

	status = -1;
	if (access(bin, F_OK | X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid < 0)
			ft_putendl("Unable to fork pid");
		else if (child_pid == 0)
		{
			execve(bin, args, g_env);
		}
		else
			waitpid(child_pid, &status, 0);
		return (1);
	}
	return (0);
}

int				cmd_exec(char *bin, char **args)
{
	char		**envpaths;
	pid_t		child_pid;
	int			i;
	int 		status;

	status = -1;
	i = -1;
	if (cmd_exec_woenv(bin, args))
		return (1);
	if (!(envpaths = get_envpaths(bin)))
		return (0);
	while (envpaths[++i])
	{
		if (access(envpaths[i], F_OK | X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid < 0)
				ft_putendl("Unable to fork pid");
			else if (child_pid == 0)
				execve(envpaths[i], args, g_env);
			else
				waitpid(child_pid, &status, 0);
			ft_free_twodm(envpaths);
			return (1);
		}
	}
	ft_free_twodm(envpaths);
	return (0);
}