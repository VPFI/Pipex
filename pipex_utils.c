/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:40:59 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/22 18:02:24 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_all(int childs)
{
	while (0 < childs)
	{
		wait(0);
		//printf("Waited for child %i: %i\n", -(childs) + 3, wait(0));
		childs--;
	}
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
		else if (envp[i])
			return(ft_split(envp[i] + 5, ':'));
		else
			return (ft_split(DEF_PATH, ':'));
	}
	return (NULL);
}