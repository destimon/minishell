/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 10:09:06 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/08 10:09:09 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

# define CMD 0

# define F_CMP(x, y) ft_strcmp(x, y)

void		commands_switch(char **query)
{
	if (F_CMP(query[CMD], ".") == 0 || F_CMP(query[CMD], "..") == 0 ||
		F_CMP(query[CMD], "/") == 0 || F_CMP(query[CMD], "~") == 0)
		cmd_cd(&query[0]);
	else if (F_CMP(query[CMD], "echo") == 0)
		cmd_echo(&query[1]);
	else if (F_CMP(query[CMD], "cd") == 0)
		cmd_cd(&query[1]);
	else if (F_CMP(query[CMD], "env") == 0)
		cmd_env(&query[1]);
	else if (F_CMP(query[CMD], "setenv") == 0)
		cmd_setenv(&query[1]);
	else if (F_CMP(query[CMD], "unsetenv") == 0)
		cmd_unsetenv(&query[1]);
	else if (F_CMP(query[CMD], "exit") == 0)
		exit (0);
	else if (cmd_exec(query[0], &query[0]) == 0)
		unknown_cmd(query[CMD]);
}

void		commands_space(char *input)
{
	char 	**query;
	int 	i;

	if (!input)
		return ;
	query = ft_strsplit(input, ' ');
	free(input);
	if (!ft_elems(query))
	{
		free(query);
		return ;
	}
	commands_switch(query);
	i = 0;
	while (query[i])
	{
		ft_strdel(&query[i]);
		i++;
	}
	free(query);
}
