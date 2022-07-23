/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:39:45 by arakhurs          #+#    #+#             */
/*   Updated: 2022/07/20 17:39:51 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_cf(int ac, char **av, t_pipex *p)
{
	if (ac != 5)
		send_err(USG_ERR);
	p->infile = open(av[1], O_RDONLY);
	p->outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);//TRUNC - if file exsist, clear it.
	if (p->infile == -1)
		send_err(OPEN_IN);
	if (p->outfile == -1)
		send_err(OPEN_OUT);
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);//ignor PATH=
}

char	*get_cmd(char	**paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, F_OK) == 0)//Tests whether the file exists.	
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	close_pipes(t_pipex *p)
{
	int	c1;
	int	c2;

	c1 = close(p->fd[0]);
	c2 = close(p->fd[1]);
	if (c2 != 0 || c1 != 0)
		send_err("CLOSE ERROR");
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;

	open_cf(ac, av, &p);
	if (pipe(p.fd) == -1)//Recives a fd[2] and opens fd[0] for reading and fd[1] for writing
		send_err(PIPE_CR);
	p.env_paths = find_path(envp);
	p.cmd_paths = ft_split(p.env_paths, ':');
	p.pid1 = fork();//Splits process creating a child process with pid 
	if (p.pid1 < 0)
		send_err(FORK_ERR);
	if (p.pid1 == 0)
		cmd1_child(p, av, envp);
	p.pid2 = fork();//Splits process creating a child process with pid 
	if (p.pid2 < 0)
		send_err(FORK_ERR);
	if (p.pid2 == 0)
		cmd2_child(p, av, envp);
	close_pipes(&p);//closing all opend pipes
	waitpid(p.pid1, NULL, 0);
	waitpid(p.pid2, NULL, 0);
	free_main(&p);//making all mallocs free
	return (0);
}
