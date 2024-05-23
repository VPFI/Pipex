/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:50:47 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/23 17:56:20 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pip_err_aux(int err, char *m)
{
	if (err == ERR_ARGS)
	{
		ft_printf(STDERR_FILENO, "pipex: invalid number of arguments\n");
		return (102);
	}
	else if (err == ERR_OUTF)
	{
		ft_printf(STDERR_FILENO, "pipex: error creating outfile: %s\n", m);
		return (73);
	}
	else if (err == ERR_COMMANDNF)
	{
		ft_printf(STDERR_FILENO, "pipex: command not found: %s\n", m);
		return (127);
	}
	else if (err == ERR_FAILEDEXE)
	{
		ft_printf(STDERR_FILENO, "pipex: command execution failed: %s\n", m);
		return (126);
	}
	else
	{
		perror("pipex");
		return (1);
	}
}

int	pip_err(int err, char *msg)
{
	if (err == ERR_MEM || err == ERR_PERM || err == ERR_NOFILE)
	{
		if (err == ERR_MEM)
			ft_printf(STDERR_FILENO, "pipex:%s cannot allocate memory\n", msg);
		else if (err == ERR_PERM)
			ft_printf(STDERR_FILENO, "pipex: permission denied: %s\n", msg);
		else if (err == ERR_NOFILE)
			ft_printf(STDERR_FILENO, "pipex: no such file or dir: %s\n", msg);
		return (1);
	}
	else
		return (pip_err_aux(err, msg));
}

void	close_pipes(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	free_all(t_pip *pipx)
{
	if (pipx)
	{
		if (pipx->cmd_path)
		{
			free(pipx->cmd_path);
			pipx->cmd_path = NULL;
		}
		free_arr(pipx->cmd_args);
		free_arr(pipx->env_paths);
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
