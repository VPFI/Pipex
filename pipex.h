/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:17:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/21 21:20:50 by vperez-f         ###   ########.fr       */
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
//Define all errors etc...

typedef struct s_pip
{
	int		argc;
	int		in_file;
	int		out_file;
	int		pipefd[2];
	char    *cmd_path;
	char	**cmd_args;
	char	**argv;
	char	**envp;
	char	**env_paths;
}			t_pip;

void	free_arr(char **arr);
void	free_all(t_pip *pipx);
void	close_pipes(t_pip *pipx);

char	*get_cmd_path(char *full_cmd, char **all_paths);
char	**get_args(char *full_cmd);
char	**get_all_paths(char **envp);

int	init_childs(t_pip *pipx);
int	exec_first_command(t_pip *pipx);
int	exec_second_command(t_pip *pipx);
int	init_pipx(t_pip *pipx, int argc, char **argv, char **envp);

#endif