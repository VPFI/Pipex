/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:41:03 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/21 21:28:04 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pip *pipx)
{
	close(pipx->pipefd[0]);
	close(pipx->pipefd[1]);
	//protect close?
}

void	free_all(t_pip *pipx)
{
	if (pipx)
	{
		if (pipx->cmd_path)
			free(pipx->cmd_path);
		free_arr(pipx->cmd_args);
		free_arr(pipx->env_paths);
	}
	free(pipx);
}
int	exec_second_command(t_pip *pipx)
{
	pipx->cmd_path = get_cmd_path(pipx->argv[3], pipx->env_paths);
	pipx->cmd_args = get_args(pipx->argv[3]);
	if (!pipx->cmd_path)
	{
		free_all(pipx);
		return (ERR_COMMANDNF);
	}
	if (dup2(pipx->pipefd[0], STDIN_FILENO) < 0)
	{
		free_all(pipx);
		return (ERR_DUP);
	}
	if (dup2(pipx->out_file, STDOUT_FILENO) < 0)
	{
		free_all(pipx);
		return (ERR_DUP);
	}
	close_pipes(pipx->pipefd);
	execve(pipx->cmd_path, pipx->cmd_args, pipx->envp);
	free_all(pipx);
	return (ERR_FAILEDEXE);
}
int	exec_first_command(t_pip *pipx)
{
	pipx->cmd_path = get_cmd_path(pipx->argv[2], pipx->env_paths);
	pipx->cmd_args = get_args(pipx->argv[2]);
	if (!pipx->cmd_path)
	{
		free_all(pipx);
		return (ERR_COMMANDNF);
	}
	if (dup2(pipx->pipefd[1], STDOUT_FILENO) < 0)
	{
		free_all(pipx);
		return (ERR_DUP);
	}
	if (dup2(pipx->in_file, STDIN_FILENO) < 0)
	{
		free_all(pipx);
		return (ERR_DUP);
	}
	close_pipes(pipx->pipefd);
	//close everytime I free?
	execve(pipx->cmd_path, pipx->cmd_args, pipx->envp);
	free_all(pipx);
	return (ERR_FAILEDEXE);
}

int	init_childs(t_pip *pipx)
{
	int		err_flag;
	pid_t	pid_child_1;
	pid_t	pid_child_2;
	
	err_flag = 0;
	pid_child_1 = fork();
	if (pid_child_1 < 0)
		return (ERR_FORK);
	if (pid_child_1 == 0)
	{
		err_flag = exec_first_command(pipx);
		err_flag = pip_err(err_flag);
		exit(0);
		// can I retrn frm func and it will kill the chld snce it's init here
	}
	pid_child_2 = fork();
	if (pid_child_2 < 0)
		return (ERR_FORK);
	if (pid_child_2 == 0)
	{
		err_flag = exec_second_command(pipx);
		err_flag = pip_err(err_flag);
		exit(0);
	}
	return (err_flag);
}
int	init_pipx(t_pip *pipx, int argc, char **argv, char **envp)
{
	pipx->argc = argc;
	pipx->argv = argv;
	pipx->envp = envp;
	if (argc < 5)
		return ((ERR_ARGS));
	pipx->out_file = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (pipx->out_file < 0)
		return ((ERR_OUTF));
	pipx->in_file = open(argv[1], O_RDONLY);
	if (pipx->in_file < 0)
	{
		if	(!access(argv[1], F_OK) && access(argv[1], R_OK))
			return ((ERR_PERM));
		else
			return ((ERR_READ));
	}	
	pipx->env_paths = get_all_paths(envp);
	if (!pipx->env_paths)
		return ((ERR_PATHS));
	if (pipe(pipx->pipefd))
		return ((ERR_PIPE));
	pipx->cmd_path = NULL;
	pipx->cmd_args = NULL;
	return (0);
}
int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		childs;
	int		err_flag;
	t_pip	*pipx;

	err_flag = 0;
	childs = argc - 3;
	pipx = (t_pip *)malloc(sizeof(pipx) * 1);
	if (!pipx)
		return (pip_err(ERR_MEM));
	err_flag = init_pipx(pipx, argc, argv, envp);
	if (err_flag)
	{
		free_all(pipx);
		return (pip_err(err_flag));
	}
	err_flag = init_childs(pipx);
	if (err_flag)
	{
		free_all(pipx);
		return (pip_err(err_flag));
	}
	close_pipes(pipx->pipefd);
	wait_all(childs);
	free_all(pipx);
	return (err_flag);
}
