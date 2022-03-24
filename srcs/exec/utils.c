/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:54:46 by mtournay          #+#    #+#             */
/*   Updated: 2022/03/24 12:55:32 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

int	cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ncmp(char *s1, char *s2, size_t n)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && n > 0)
	{
		if (s1[i] != s2[i])
			break ;
		i++;
		n--;
	}
	if (n || s1[i] || s2[i])
		return (1);
	return (0);
}

int	nl_convert(char **s)
{
	char	*ret;
	int		b;
	int		i;
	int		j;

	i = 0;
	j = 0;
	b = 0;
	ret = malloc(sizeof(char) * ft_strlen(*s) + 1);
	if (!ret)
		return (0);
	while ((*s)[i])
	{
		ret[j] = (*s)[i];
		if ((*s)[i] == '\\' && (*s)[i + 1] == 'n')
		{
			b = 1;
			ret[j] = '\n';
			i++;
		}
		i++;
		j++;
	}
	ret[j] = '\0';
	if (!b)
	{
		free(ret);
		return (1);
	}
	*s = ret;
	return (1);
}

int	dup_env(char **env, char ***var_env)
{
	int	i;

	i = 0;
	while(env[i])
		i++;
	*var_env = malloc(sizeof(char *) * (i + 1));
	if (!var_env)
		return (0);
	i = 0;
	while (env[i])
	{
		(*var_env)[i] = env[i];
		i++;
	}
	(*var_env)[i] = NULL;
	return (1);
}

void	free_varenv(char **var, char *last)
{
	int	j;

	j = 0;
	while (cmp(var[j], last))
		j++;
	j++;
	while (var[j])
	{
		free(var[j]);
		j++;
	}
	free(var);
}

char	*cat_dup(char *dst, char *src)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(sizeof(char) * (ft_strlen(dst) + ft_strlen(src) + 2));
	if (!ret)
	{
		free(dst);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (dst[++i])
		ret[i] = dst[i];
	ret[i++] = '/';
	while (src[j])
		ret[i++] = src[j++];
	ret[i] = '\0';
	free(dst);
	return (ret);
}