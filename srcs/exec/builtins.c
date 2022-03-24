/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:55:25 by mtournay          #+#    #+#             */
/*   Updated: 2022/03/24 16:36:57 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

int get_cd(char **buf)
{
	int		i;

	i = 1;

	*buf =  malloc(sizeof(char) *i );
	if (!buf)
		return (0);
	while(!getcwd(*buf,i))
	{
		free(*buf);
		i++;
		*buf =  malloc(sizeof(char) * i);
		if (!*buf)
			return (0);
	}
	return (1);
}

int	ft_pwd(char **cmd)
{
	char	*buf;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 1)					// input error
	{
		write(1, "pwd: too many arguments\n", 24);
		return (1); 
	}
	if(!get_cd(&buf))
		return (0);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	return (1);
}

static char	*dot_dot(char *buf, char *ret)
{
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(buf);
	while (buf[i] != '/')
		i--;
	ret = malloc(sizeof(char) * i + 1);
	if (!ret)
		return (0);
	while (j < i)
	{
		ret[j] = buf[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

int	ft_cd(char **cmd)
{
	char 	*buf;
	char 	*new_dest;
	int		i;

	i = 0;
	new_dest = NULL;
	while (cmd[i])
		i++;
	if (!cmd[1])
	{
		new_dest = ft_strjoin("/Users/", getenv("USER"));
		chdir(new_dest);
		free(new_dest);
		return (1);
	}
	if (i >= 3)         // input error
	{
		write(1, "cd: string not in pwd: ", 23);
		write(1, cmd[1], ft_strlen(cmd[1]));
		write(1, "\n", 1);
		return (1);
	}
	if (!get_cd(&buf))
		return (0);
	if (!ft_strncmp(cmd[1], "..", 3))
	{
		new_dest = dot_dot(buf, new_dest);
		if (!new_dest)
			return (0);
		chdir(new_dest);
		free(new_dest);
		free(buf);
		return (1);
	}
	if (cmd[1][0] == '/')
	{
		if (chdir(cmd[1]) == -1)
		{
			write(1,"cd: no such file or directory: ", 30);
			write(1, cmd[1], ft_strlen(cmd[1]));
			write(1, "\n", 1);
		}
		free(buf);
	}
	else
	{
		new_dest = ft_strjoin(buf, cmd[1]);
		if (!new_dest)
			return (0);
		if (chdir(cmd[1]) == -1)
		{
			write(1,"cd: no such file or directory: ", 30);
			write(1, cmd[1], ft_strlen(cmd[1]));
			write(1, "\n", 1);
		}
		free(new_dest);
		free(buf);
	}
	return (1);
}

int	ft_echo(char **cmd, char **env)   // (opt = 1) = -n / else opt = 0
{
	int		i;
	int		j;
	int 	k;
	int		f;
	int		len;

	i = 0;
	j = 0;
	f = 0;
	k = 0;
	if (cmd[1])
		if (!ncmp(cmd[1], "-n", 2))
			f = 1;
	if (cmd[f + 1])
	{
		while (cmd[k + f])
		{
			if (!nl_convert(&cmd[k + f]))
				return (0);
			k++;
		}
		k = 1;
		if (!ncmp(cmd[1 + f], "-", 1))
			k++;
		if (!cmd[f + k])
		{
			if (!f)
				write(1, "\n", 1);
			return (1);
		}
		if (cmd[f + k][i] == '$')
		{
			if (!cmd[f + k][i + 1])
				write(1, "$", 1);
			else
			{
				len = ft_strlen(cmd[f + k]);
				while (env[j])
				{
					if (!ncmp(cmd[f + k], env[j], len))
					{
						if (env[j][++len] == '=')
							break ;
					}
					j++;
				}
				ft_putstr_fd(env[j] + len, 1);
				len = ft_strlen(env[j]);
				if (f && env[j][len - 1] != '\n')
				{
					write(1, "%%", 1);
					return (1);
				}

			}
		}
		while (cmd[f + k])
		{
			ft_putstr_fd(cmd[f + k], 1);
			if (cmd[f + k + 1])
				write(1, " ", 1);
			k++;
		}
	}
	if (!f)
		write(1, "\n", 1);
	return (1);
}

int	ft_export(char ***env, char **cmd)
{
	char	**ret;
	int		i;
	int		j;
	i = 0;
	j = 0;
	while ((*env)[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (0);
	while (j < i)
	{
		ret[j] = (*env)[j];
		j++;
	}
	ret[i] = ft_strdup(cmd[1]);	
	if (!ret[i])
		return (0);
	i++;
	ret[i] = NULL;
	free(*env);
	*env = ret;
	return (1);
}

int	ft_unset(char ***env, char **cmd)
{
	int		i;
	char	**ret;

	i = 0;
	while((*env)[i])
		i++;
	ret = malloc(sizeof(char *) * i);
	if (!ret)
		return (0);
	i = 0;
	while(cmp((*env)[i], cmd[1]) && (*env)[i])
	{
		ret[i] = (*env)[i];
		i++;
	}
	if (!(*env)[i])
	{
		free(ret);
		return (1);
	}
	i++;
	free((*env)[i -1]);
	while ((*env)[i])
	{
		ret[i - 1] = (*env)[i];
		i++;
	}
	ret[i - 1] = NULL;
	free(*env);
	*env = ret;
	return (1);
}

int	ft_env(char **env, char **cmd)
{
	int	i;
	int	len;
	
	if (cmd[1])
	{
		write(1, "env: ", 5);
		write(1, cmd[1], ft_strlen(cmd[1]));
		write(1, ": No such file or directory\n", 27);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		write(1, env[i], len);
		write(1, "\n", 1);
		i++;
	}
	return (1);
}
