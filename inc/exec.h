/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:48:45 by mtournay          #+#    #+#             */
/*   Updated: 2022/03/24 16:02:33 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <signal.h>


int     get_cd(char **buf);
int	    ft_pwd(char **cmd);
int	    ft_cd(char **cmd);
int	    ft_echo(char **cmd, char **env);
int	    ft_unset(char ***env, char **cmd);
int	    ft_export(char ***env, char **cmd);
int	    ft_env(char **env, char **cmd);

int 	cmp(char *s1, char *s2);
int	    ncmp(char *s1, char *s2, size_t n);
int	    nl_convert(char **s);
int	    dup_env(char **env, char ***var_env);
void	free_varenv(char **var, char *last);

int bin_cmd(char ***env, char **cmd);

char	*cat_dup(char *dst, char *src);

#endif