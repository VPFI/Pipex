/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:41:03 by vperez-f          #+#    #+#             */
/*   Updated: 2024/07/10 19:04:40 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_second_command(t_pip *pipx)
{
	if (check_path(pipx->argv[3]))
		pipx->cmd_path = ft_strdup(pipx->argv[3]);
	else
		pipx->cmd_path = get_cmd_path(pipx->argv[3], pipx->env_paths);
	pipx->cmd_args = get_args(pipx->argv[3]);
	if (!pipx->cmd_path)
	{
		free_all(pipx);
		exit(pip_err(ERR_COMMANDNF, (ft_split(pipx->argv[3], ' ')[0])));
	}
	if (dup2(pipx->pipefd[0], STDIN_FILENO) < 0)
	{
		free_all(pipx);
		exit(pip_err(ERR_STD, NULL));
	}
	if (dup2(pipx->out_file, STDOUT_FILENO) < 0)
	{
		free_all(pipx);
		exit(pip_err(ERR_STD, NULL));
	}
	close_pipes(pipx->pipefd);
	execve(pipx->cmd_path, pipx->cmd_args, pipx->envp);
	free_all(pipx);
	exit(pip_err(ERR_STD, NULL));
}

void	exec_first_command(t_pip *pipx)
{
	if (check_path(pipx->argv[2]))
		pipx->cmd_path = ft_strdup(pipx->argv[2]);
	else
		pipx->cmd_path = get_cmd_path(pipx->argv[2], pipx->env_paths);
	pipx->cmd_args = get_args(pipx->argv[2]);
	if (!pipx->cmd_path)
	{
		free_all(pipx);
		exit(pip_err(ERR_COMMANDNF, (ft_split(pipx->argv[2], ' ')[0])));
	}
	if (dup2(pipx->pipefd[1], STDOUT_FILENO) < 0)
	{
		free_all(pipx);
		exit(pip_err(ERR_STD, NULL));
	}
	if (dup2(pipx->in_file, STDIN_FILENO) < 0)
	{
		free_all(pipx);
		exit(pip_err(ERR_STD, NULL));
	}
	close_pipes(pipx->pipefd);
	execve(pipx->cmd_path, pipx->cmd_args, pipx->envp);
	free_all(pipx);
	exit(pip_err(ERR_STD, NULL));
}

void	init_childs(t_pip *pipx)
{
	pipx->pid_child_1 = fork();
	if (pipx->pid_child_1 < 0)
	{
		free_all(pipx);
		exit(pip_err(ERR_MEM, " fork:"));
	}
	if (pipx->pid_child_1 == 0)
		exec_first_command(pipx);
	pipx->pid_child_2 = fork();
	if (pipx->pid_child_2 < 0)
	{
		free_all(pipx);
		exit(pip_err(ERR_MEM, " fork:"));
	}
	if (pipx->pid_child_2 == 0)
		exec_second_command(pipx);
	return ;
}

void	init_pipx(t_pip *pipx, int argc, char **argv, char **envp)
{
	pipx->argv = argv;
	pipx->envp = envp;
	if (argc != 5)
		exit(pip_err(ERR_ARGS, NULL));
	pipx->out_file = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (pipx->out_file < 0)
		exit(pip_err(ERR_OUTF, argv[argc - 1]));
	pipx->in_file = open(argv[1], O_RDONLY);
	if (pipx->in_file < 0)
	{
		if (access(argv[1], F_OK))
			exit(pip_err(ERR_NOFILE, argv[1]));
		else if (access(argv[1], R_OK))
			exit(pip_err(ERR_PERM, argv[1]));
		else
			exit(pip_err(ERR_STD, NULL));
	}
	pipx->env_paths = get_all_paths(envp);
	if (pipe(pipx->pipefd))
		exit(pip_err(ERR_STD, NULL));
	pipx->cmd_path = NULL;
	pipx->cmd_args = NULL;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	int		childs;
	int		stat;
	t_pip	pipx;

	childs = argc - 3;
	init_pipx(&pipx, argc, argv, envp);
	init_childs(&pipx);
	close_pipes(pipx.pipefd);
	stat = wait_all(&pipx, childs);
	free_all(&pipx);
	return (WEXITSTATUS(stat));
}
