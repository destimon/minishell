/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 10:20:01 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/08 10:20:02 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void 			unknown_cmd(char *cmd)
{
	ft_putstr(cmd);
	ft_putendl(": unknown command");
}

void			cd_errors(char *err)
{
	if (err)
	{
		ft_putstr("cd: ");
		ft_putendl(err);
	}
	return ;
}