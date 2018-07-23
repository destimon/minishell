/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 09:39:24 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/17 13:35:00 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int					is_user_a_goat(void)
{
	return (1);
}

void				free_env(void)
{
	int				i;

	i = 0;
	while (g_env[i])
	{
		free(g_env[i]);
		i++;
	}
	free(g_env);
}

static void			init_loop(void)
{
	char			*line;
	char			**cmds;
	int				i;

	while (is_user_a_goat())
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
	}
}

int					main(void)
{
	g_env = g_get_env();
	signals();
	help_out();
	init_loop();
	free_env();
	return (0);
}
