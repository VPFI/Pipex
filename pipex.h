/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:17:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/22 19:53:56 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

# define DEF_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

# define ERR_STD  1 //perror
# define ERR_MEM  2 //1
# define ERR_ARGS  3 //102
# define ERR_OUTF  4 //73
# define ERR_PERM  5 //1
# define ERR_NOFILE 6 //1
# define ERR_COMMANDNF 7 //127
# define ERR_FAILEDEXE 8 //126

typedef struct s_pip
{
	int		argc;
	int		in_file;
	int		out_file;
	int		pipefd[2];
	pid_t	pid_child_1;
	pid_t	pid_child_2;
	char	*cmd_path;
	char	**cmd_args;
	char	**argv;
	char	**envp;
	char	**env_paths;
}			t_pip;

int		wait_all(t_pip *pipx, int childs);
int		pip_err(int err, char *msg);
int		pip_err_aux(int err, char *msg);

char	*get_cmd_path(char *full_cmd, char **all_paths);
char	**get_args(char *full_cmd);
char	**get_all_paths(char **envp);

void	free_arr(char **arr);
void	free_all(t_pip *pipx);
void	close_pipes(int *pipefd);
void	init_childs(t_pip *pipx);
void	exec_first_command(t_pip *pipx);
void	exec_second_command(t_pip *pipx);
void	init_pipx(t_pip *pipx, int argc, char **argv, char **envp);

#endif