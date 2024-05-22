/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:59 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/22 20:08:20 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_all(t_pip *pipx, int childs)
{
	int	final_stat;
	int	id1;
	int	id2;

	final_stat = 0;
	id1 = waitpid(pipx->pid_child_1, &final_stat, 0);
	childs--;
	id2 = waitpid(pipx->pid_child_2, &final_stat, 0);
	childs--;
	return (final_stat);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
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
		if ((!access(cmd, F_OK)))
		{
			if (!access(cmd, X_OK))
				return (cmd);
			else
				exit(pip_err(ERR_FAILEDEXE, cmd));
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
		i++;
	}
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
		else if (envp[i])
			return (ft_split(envp[i] + 5, ':'));
		else
			return (ft_split(DEF_PATH, ':'));
	}
	return (NULL);
}
