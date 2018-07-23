/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcherend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/08 09:39:49 by dcherend          #+#    #+#             */
/*   Updated: 2018/07/08 09:40:28 by dcherend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "../lib/libft/get_next_line.h"
# include <unistd.h>
# include <sys/syslimits.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>
# include <sys/types.h>
# include <string.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>

# define ERR_CD_MANYARGS	"too many arguments"
# define ERR_CD_UNEXIST		"no such file or directory"
# define ERR_CD_UNACCESS	"Permission denied."

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

# define ANSI_BOLD_GREEN		"\e[1;32m"
# define ANSI_BOLD_WHITE		"\e[1;37m"

char			**g_env;
pid_t			g_curr_job;

/*
** CORE.
*/
void			commands_space(char *input);

/*
** CMD.
*/
void			cmd_echo(char **strings);
void			cmd_cd(char **dirs);
int				cmd_exec(char *bin, char **argc);

/*
** CMD_ENV.
*/
void			cmd_env(char **args);
void			cmd_setenv(char **envs);
int				cmd_resetenv(char *name, char *env);
void			cmd_unsetenv(char **envs);

/*
** UTILS.
*/
char			**g_get_env(void);
void			show_prompt(void);
char			*get_path(void);
void			g_free_env(void);
char			**get_envpaths(char *bin);

/*
** UTILS2.
*/
char			*get_var(char *var);
void			set_var(char *name, char *var);
char			*path_homecut(char *path);
char			*var_namecut(char *var);
void			add_var(char **envs, int size);
void			help_out(void);

/*
** ENVMANAGE.
*/
char			**realloc_env(size_t size);
char			**realloc_less(char **todel, size_t size);
int				is_exist(char **todel, char *env);

/*
** SIGNALS.
*/
void			signals(void);
int				search_env(int *i);

/*
** ERROR.
*/
void			unknown_cmd(char *cmd);
void			cd_errors(char *err);

#endif
