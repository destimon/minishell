/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 09:39:24 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/08 09:39:40 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//◦ malloc, free
//◦ access
//◦ open, close, read, write
//◦ opendir, readdir, closedir
//◦ getcwd, chdir
//◦ stat, lstat, fstat
//◦ fork, execve
//◦ wait, waitpid, wait3, wait4
//◦ signal, kill
//◦ exit

//• builtins: echo, cd, setenv, unsetenv, env, exit.

//	Strange loops in cmd_exec(cmd.c)
//	Also need to work on echo and cd hardly

int					is_user_a_goat(void)
{
	return (1);
}

void				free_env(void)
{
	int 			i;

	i = 0;
	while (g_env[i])
	{
		free(g_env[i]);
		i++;
	}
	free(g_env);
}

int					main(int argc, char **argv)
{
	char			*line;
	char 			**cmds;
	int 			i;

	g_env = g_get_env();
	signals();
	while(is_user_a_goat())
	{
		i = -1;
		show_prompt();
		if ((get_next_line(2, &line) > 0))
		{
			if (ft_strlen(line) > 0)
			{
				cmds = ft_strsplit(line, ';');
				free(line);
				while (cmds[++i])
					commands_space(cmds[i]);
				while (cmds[i])
					free(cmds[i--]);
				free(cmds);
			}
			else
				free(line);
		}
		system("leaks -q minishell");
	}
	free_env();
	return (0);
}
