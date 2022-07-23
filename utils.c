/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:40:05 by arakhurs          #+#    #+#             */
/*   Updated: 2022/07/20 17:40:09 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	send_err(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);//error
	else
		perror(s);//find and print each error line
	exit(1);//cmd + c
}

void	free_main(t_pipex *p)
{
	int	i;

	i = 0;
	close_cf(p);
	while (p->cmd_paths[i])
		free(p->cmd_paths[i++]);
	free(p->cmd_paths);
}

void	free_cmd(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->cmd_args[i])
		free(p->cmd_args[i++]);
	free(p->cmd_args);
	free(p->cmd);
}
