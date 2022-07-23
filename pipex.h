/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 17:42:22 by arakhurs          #+#    #+#             */
/*   Updated: 2022/07/20 17:42:27 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>//for close, pipe, dup2
# include <fcntl.h>//for open
# include <stdlib.h>// for malloc, free, exit
# include <sys/wait.h>// for waitpid
# include <errno.h>// for errno
# include <stdio.h>// for perror

# define USG_ERR	"❌ Type ❗️./pipex [file1] [cmd1] [cmd2] [file2]❗️"
# define OPEN_IN	"❌ Open ❗️input❗️"
# define OPEN_OUT	"❌ Open ❗️output❗️"
# define PIPE_CR	"❌ Pipe ❗️creation❗️"
# define PIPE_CL	"❌ Pipe ❗️close❗️"
# define FORK_ERR	"❌ Fork ❗️you lose yor child 😢"
# define CMD_ERR	"❌ Command"
# define DUP2_ERR	"❌ DUP2"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		infile;
	int		outfile;
	char	*env_paths;
	char	**cmd_args;
	char	**cmd_paths;
	char	*cmd;
}				t_pipex;

void	send_err(char *s);
void	open_cf(int ac, char **av, t_pipex *p);
char	*find_path(char **envp);
char	*get_cmd(char **paths, char *cmd);
void	cmd1_child(t_pipex p, char **av, char **envp);
void	cmd2_child(t_pipex p, char **av, char **envp);
void	close_pipes(t_pipex *p);
void	free_main(t_pipex *p);
void	close_cf(t_pipex *p);
void	free_cmd(t_pipex *p);

#endif
