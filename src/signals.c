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
	printf("\n");
	show_prompt();
}

void			signals(void)
{
	signal(SIGINT, &ft_sigint));
}