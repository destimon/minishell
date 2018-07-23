/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/11 18:15:00 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/11 18:15:02 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void				ft_sigint(int sig)
{
	if (g_curr_job > 1)
	{
		sig = 0;
		return ;
	}
	ft_putendl("");
	show_prompt();
}

void				ft_sigstop(int sig)
{
	sig = 0;
	return ;
}

void				signals(void)
{
	signal(SIGINT, &ft_sigint);
	signal(SIGTSTP, &ft_sigstop);
}

/*
** This fucking norminette forces me do pain to the functions ... ...
*/

int					search_env(int *i)
{
	while (g_env[++(*i)])
		if (ft_strstr(g_env[*i], "PATH="))
		{
			return (1);
		}
	return (0);
}
