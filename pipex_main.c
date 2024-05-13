/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:17:09 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/13 19:01:38 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)	
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr[i]);
		free(arr);
	}
}

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
	while (all_paths[i])
	{
		cmd = ft_strjoin(all_paths[i], temp);
		if ((!access(cmd, F_OK)) && (!access(cmd, X_OK)))
		{
			//printf("OK out %s\n", cmd);
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
		//printf("arg[%i]: %s  ", i, arg[i]);
		i++;
	}
	//printf("\n");
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
	pid_t	pid_child_1;
	pid_t	pid_child_2;
	int		pipefd[2];
	int		in_file;
	int		out_file;
	char    *cmd_path;
	char	**cmd_args;
	char	**actual_normal_human_paths;

	i = 2;
	in_file = open(argv[1], O_RDONLY);
	if (in_file < 0)
		return (printf("Failed to open/read in_file\n"));
	out_file = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (out_file < 0)
		return(printf("Failed to open/create out_file\n"));
	actual_normal_human_paths = get_all_paths(envp);
	cmd_path = NULL;
	cmd_args = NULL;
	/*
	i = 0;
	while (actual_normal_human_paths[i])
	{
		printf("arg[%i]: %s\n", i, actual_normal_human_paths[i]);
		i++;
	}*/
	if (pipe(pipefd))
		return (1);
	pid_child_1 = fork();
	if (pid_child_1 < 0)
		return (2);
	if (pid_child_1 == 0)
	{
		//printf("Child 1: %i\n", getpid());
		//close(pipefd[0]);
		cmd_path = get_cmd_path(argv[i], actual_normal_human_paths);
		cmd_args = get_args(argv[i]);
		dup2(pipefd[1], STDOUT_FILENO);
		dup2(in_file, STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(cmd_path, cmd_args, envp);
		//technically should free stuff if execve fails
		exit(0);
		
	}
	pid_child_2 = fork();
	if (pid_child_2 < 0)
		return (3);
	if (pid_child_2 == 0)
	{
		//printf("Child 2: %i\n", getpid());
		i++;
		cmd_path = get_cmd_path(argv[i], actual_normal_human_paths);
		cmd_args = get_args(argv[i]);
		dup2(pipefd[0], STDIN_FILENO);
		dup2(out_file, STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(cmd_path, cmd_args, envp);
		exit(0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	while (0 < (argc - 3))
	{
		wait(0);
		//printf("Waited for child %i: %i\n", -(argc - 3) + 3, wait(0));
		argc--;
	}
	free_arr(actual_normal_human_paths);
	return (0);
}
