/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_comm_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:59 by vperez-f          #+#    #+#             */
/*   Updated: 2024/07/10 18:58:49 by vperez-f         ###   ########.fr       */
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

int	check_path(char *path)
{
	int	i;

	i = 0;
	if (path)
	{
		while (path[i])
		{
			if (path[i] == '/')
			{
				return (1);
			}
			i++;
		}
		return (0);
	}
	return (0);
}

char	*get_cmd_path(char *full_cmd, char **all_paths)
{
	char	*cmd;
	char	*temp;
	char	**list_temp;
	int		i;

	i = 0;
	list_temp = ft_split(full_cmd, ' ');
	temp = ft_strjoin("/", list_temp[0]);
	free_arr(list_temp);
	while (all_paths && all_paths[i] && temp)
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
