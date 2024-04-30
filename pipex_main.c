/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:17:09 by vperez-f          #+#    #+#             */
/*   Updated: 2024/04/30 11:42:26 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_path(char *full_cmd, char **all_paths)
{
	char	*cmd;
	char	*temp;
	int		i;

	i = 0;
	temp = ft_split(full_cmd, ' ')[0];
	cmd = temp;
	temp = ft_strjoin("/", temp);
	free(cmd);
	printf("cmd: %s\n", temp);
	while (all_paths[i])
	{
		cmd = ft_strjoin(all_paths[i], temp);
		printf("cmd_path: %s\n", cmd);
		if ((!access(cmd, F_OK)) && (!access(cmd, X_OK)))
		{
			printf("OK out %s\n", cmd);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	if (temp)
		free(temp);
	return (NULL);
}
char	**get_args(char *full_cmd)
{
	char	**arg;
	int		i;

	i = 0;
	arg = ft_split(full_cmd, ' ');
	while (arg[i])
	{
		printf("arg[%i]: %s  ", i, arg[i]);
		i++;
	}
	printf("\n");
	return (arg);
}
char	**get_all_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strnstr(envp[i], "PATH=", 5))
			i++;
		else
		{
			return(ft_split(envp[i] + 5, ':'));
		}
	}
	return (NULL);
}
int	main(int argc, char **argv, char** envp)
{
	int		i;
	pid_t	pid;
	int		pipefd[2];
	int		in_file;
	int		out_file;
	char    *cmd_path;
	char	**cmd_args;
	char	**actual_normal_human_paths;

	i = 2;
	pid = 0;
	in_file = open(argv[1], O_RDONLY);
	out_file = open(argv[argc - 1], O_RDWR);
	actual_normal_human_paths = get_all_paths(envp);
	printf("hola\n");
	/*
	i = 0;
	while (actual_normal_human_paths[i])
	{
		printf("arg[%i]: %s\n", i, actual_normal_human_paths[i]);
		i++;
	}*/
	printf("%i\n", pid);
	pipe(pipefd);
	pid = fork();
	printf("%i\n", pid);
	if (pid == 0)
	{
		printf("hola22\n");
		i++;
		cmd_path = get_cmd_path(argv[i], actual_normal_human_paths);
		cmd_args = get_args(argv[i]);
		dup2(pipefd[0], 0);
		dup2(0, in_file);
		close(pipefd[1]);
		execve(cmd_path, cmd_args, envp);
	}
	else
	{
		printf("hola33\n");
		cmd_path = get_cmd_path(argv[i], actual_normal_human_paths);
		cmd_args = get_args(argv[i]);
		dup2(pipefd[1], 1);
		dup2(1, out_file);
		close(pipefd[0]);
		execve(cmd_path, cmd_args, envp);
	}
	close(pipefd[0]);
    close(pipefd[1]);
    wait(&pid);
}