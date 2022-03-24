/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:15:17 by lmajerus          #+#    #+#             */
/*   Updated: 2022/03/24 15:44:24 by mtournay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir(t_red *red, t_token *head)
{
	int	fd;

	if (red->file_name)
		free(red->file_name);
	red->file_name = ft_strdup_2(head->next->data);
	if (!ft_strncmp_2(head->data, ">>", 2))
		red->flags = (O_CREAT | O_APPEND | O_RDWR);
	else if (!ft_strncmp_2(head->data, "<<", 2))
		return (ft_lstadd_back_2(&red->doc, ft_lstnew_2(ft_strdup_2(red->file_name))),
			red->flags = -1, 0);
	else if (!ft_strncmp_2(head->data, ">", 1))
		red->flags = (O_CREAT | O_TRUNC | O_RDWR);
	else if (!ft_strncmp_2(head->data, "<", 1))
		red->flags = O_RDONLY;
	fd = open(red->file_name, red->flags, 0644);
	if (fd == -1)
		return (ft_error(red->file_name, 1));
	close(fd);
	return (0);
}

int	free_cmds(t_cmd *cmds, int nb_cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_cmd)
	{
		j = 0;
		while (cmds[i].av[j])
			free(cmds[i].av[j++]);
		if (cmds[i].av)
			free(cmds[i].av);
		if (cmds[i].redir_in.file_name)
			free(cmds[i].redir_in.file_name);
		if (cmds[i].redir_out.file_name)
			free(cmds[i].redir_out.file_name);
		i++;
	}
	if (cmds)
		free(cmds);
	return (1);
}

int	free_tokens(t_token **head)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->data);
		free(*head);
		*head = tmp;
	}
	return (1);
}