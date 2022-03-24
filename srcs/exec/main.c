// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mtournay <mtournay@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/02/11 11:59:59 by mtournay          #+#    #+#             */
// /*   Updated: 2022/02/16 16:41:10 by mtournay         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../inc/exec.h"



// int main(int argc, char **argv, char *envp[])
// {
// 	int i;
// 	char **var_env;
// 	char *last;
// 	char **cmd;


// 	argc = 0;
// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	last = ft_strdup(envp[i - 1]);
// 	if (!dup_env(envp, &var_env))
// 		return (0);
// 	i = 1;
// 	cmd = ft_split(argv[i], ' ');
// 	if (!cmd)
// 		return (0);
// 	i = 0;
// 	if (!bin_cmd(&var_env, cmd))
// 		return (0);
// }
