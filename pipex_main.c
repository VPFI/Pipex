/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:17:09 by vperez-f          #+#    #+#             */
/*   Updated: 2024/04/30 04:24:19 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_path(char *full_cmd, char **all_paths)
{
	char	*cmd;
	char	*temp;
	int		i;

	i = 0;
	cmd = ft_split(full_cmd, ' ')[0];
	temp = cmd;
	cmd = ft_strjoin("/", temp);
	free(temp);
	printf("cmd: %s\n", cmd);
	while (all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], cmd);
		printf("temp_path: %s\n", temp);
		if ((!access(temp, F_OK)) && (!access(temp, X_OK)))
		{
			printf("OK out %s\n", temp);
			return (temp);
		}
		free(temp);
		i++;
	}
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
	int		in_file;
	int		out_file;
	char    *cmd_path;
	char	**cmd_args;
	char	**actual_normal_human_paths;

	i = 2;
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
	}
	while (i < argc - 1)
	{
	}
	*/
	cmd_path = get_cmd_path(argv[i], actual_normal_human_paths);
	cmd_args = get_args(argv[i]);
	printf("hola222\n");
	execve(cmd_path, cmd_args, envp);
	printf("hola333\n");
}