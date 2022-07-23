/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:20:03 by arakhurs          #+#    #+#             */
/*   Updated: 2022/07/22 11:20:09 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd1_child(t_pipex p, char **av, char **envp)
{
	if (close(p.fd[0]) == -1)
		send_err(PIPE_CL);
	if (dup2(p.infile, STDIN_FILENO) == -1)//STDIN_FILENO = fd[]
		send_err(DUP2_ERR);//Closes newfd if needed, then duplicates oldfd into newfd
	if (dup2(p.fd[1], STDOUT_FILENO) == -1)//STDIN_FILENO - fd[]
		send_err(DUP2_ERR);//Closes newfd if needed, then duplicates oldfd into newfd
	if (close(p.fd[1]) == -1)
		send_err(PIPE_CL);
	p.cmd_args = ft_split(av[2], ' ');
	p.cmd = get_cmd(p.cmd_paths, p.cmd_args[0]);//Receives full path of executable, NULL-terminated array of parameters, and environment. 
												//Replaces current process with that of the specified command
	if (!p.cmd)
	{
		free_cmd(&p);
		send_err(CMD_ERR);
	}
	execve(p.cmd, p.cmd_args, envp);//executes the program pointed to by filename. 
									//filename must be either a binary executable, or a script starting with a line of the form:
}

void	cmd2_child(t_pipex p, char **av, char **envp)
{
	if (close(p.fd[1]) == -1)
		send_err(PIPE_CL);
	if (dup2(p.fd[0], STDIN_FILENO) == -1)//STDIN_FILENO = fd[]
		send_err(DUP2_ERR);//Closes newfd if needed, then duplicates oldfd into newfd
	if (dup2(p.outfile, STDOUT_FILENO) == -1)//STDIN_FILENO - fd[]
		send_err(DUP2_ERR);//Closes newfd if needed, then duplicates oldfd into newfd
	if (close(p.fd[0]) == -1)
		send_err(PIPE_CL);
	p.cmd_args = ft_split(av[3], ' ');
	p.cmd = get_cmd(p.cmd_paths, p.cmd_args[0]);//Receives full path of executable, NULL-terminated array of parameters, and environment. 
												//Replaces current process with that of the specified command
	if (!p.cmd)
	{
		free_cmd(&p);
		send_err(CMD_ERR);
	}
	execve(p.cmd, p.cmd_args, envp);
}

void	close_cf(t_pipex *p)
{
	int	c1;
	int	c2;

	c1 = close(p->infile);
	c2 = close(p->outfile);
	if (c2 != 0 || c1 != 0)
		send_err("CLOSE ERROR");
}
