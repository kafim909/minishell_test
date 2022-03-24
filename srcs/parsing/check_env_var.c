/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:13:21 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/24 16:31:32 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*delete_macro(char *str, int macro_len, int strlen)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (strlen - macro_len));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] != '$')
	{
		new[i] = str[i];
		i++;
	}
	j = i;
	i += macro_len + 1;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);
}

static int	is_space_quotes(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f'
		|| c == '\'' || c == '\"');
}

static void	replace_env_var(char *str, char *new, char *var, int macro_len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (str[i] != '$')
	{
		new[i] = str[i];
		i++;
	}
	j = i + macro_len + 1;
	k = 0;
	while (var[k])
		new[i++] = var[k++];
	while (str[j])
		new[i++] = str[j++];
	new[i] = '\0';
	free(str);
}

static char	*get_env_var(char *str, int strlen, int i)
{
	int		macro_len;
	char	*macro;
	int		var_len;
	char	*var;
	char	*new;

	macro_len = 0;
	var_len = 0;
	while (str[i++] != '$')
		;
	while (!is_space_quotes(str[i + macro_len]) && str[i + macro_len])
		macro_len++;
	macro = ft_substr_2(str, i, macro_len);
	var = getenv(macro);
	if (!var)
		return (delete_macro(str, macro_len, strlen));
	else
	{
		var_len = ft_strlen_2(var);
		new = malloc(sizeof(char) * (strlen + var_len - macro_len));
		if (!new)
			return (NULL);
		replace_env_var(str, new, var, macro_len);
	}
	return (new);
}

int	check_env_var(t_token *token)
{
	int	i;

	while (token)
	{
		i = 0;
		while (token->type == OTHER && token->data[i])
		{
			if (token->data[i] == '\"' && ++i)
				while (token->data[i] != '\"' && token->data[i]
					!= '$' && token->data[i])
					i++;
			if (token->data[i] == '\'' && ++i)
				while (token->data[i] != '\'' && token->data[i])
					i++;
			if (token->data[i] == '$' && ++i && token->data[i]
				&& token->data[i] != ' ' && token->data[i] != '?')
				token->data = get_env_var(token->data,
						ft_strlen_2(token->data), 0);
			if (token->data == NULL)
				return (0);
			i++;
		}
		token = token->next;
	}
	return (1);
}
