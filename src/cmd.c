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
#include <stdio.h>

static _Bool	cmd_echo_cases(char *str)
{
	char		*var;

	if (((str[0] == '$') && ft_strlen(str) > 1))
	{
		if ((var = get_var(&str[1])))
		{
			ft_puts_except(var, '\"');
			free(var);
			return (1);
		}
	}
	else if (str[0] == '~')
	{
		if ((var = get_var("HOME")))
			ft_puts_except(var, '\"');
		free(var);
		return (1);
	}
	else
	{
		ft_puts_except(str, '\"');
		return (1);
	}
	return (0);
}

void			cmd_echo(char **strings)
{
	int			i;
	_Bool		endl;

	endl = 0;
	if (!strings)
		return ;
	i = -1;
	while (strings[++i])
	{
		if (endl)
			ft_putstr(" ");
		endl = cmd_echo_cases(strings[i]);
	}
	ft_putendl("");
}

static int		cmd_exec_woenv(char *bin, char **args)
{
	int			status;
	pid_t		child_pid;

	status = -1;
	if (access(bin, F_OK) == 0)
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

void			do_process(char *env, char **args)
{
	pid_t		child_pid;
	int			status;

	status = -1;
	child_pid = fork();
	if (child_pid < 0)
		ft_putendl("Unable to fork pid");
	else if (child_pid == 0)
	{
		g_curr_job = child_pid;
		execve(env, args, g_env);
	}
	else
	{
		g_curr_job = child_pid;
		waitpid(child_pid, &status, 0);
	}
}

int				cmd_exec(char *bin, char **args)
{
	char		**envpaths;
	int			i;

	i = -1;
	if (cmd_exec_woenv(bin, args))
		return (1);
	if (!(envpaths = get_envpaths(bin)))
		return (0);
	while (envpaths[++i])
		if (access(envpaths[i], F_OK) == 0)
		{
			if (access(envpaths[i], X_OK) != 0)
			{
				ft_putendl("Permission denied");
				ft_free_twodm(envpaths);
				return (1);
			}
			do_process(envpaths[i], args);
			ft_free_twodm(envpaths);
			g_curr_job = -1;
			return (1);
		}
	ft_free_twodm(envpaths);
	return (0);
}
