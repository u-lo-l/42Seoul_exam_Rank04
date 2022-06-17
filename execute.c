//EXECUTE
#include "microshell.h"

void	do_single_cd(t_node *node)
{
	if (!node)
		ft_putstr_fd(2, "error: fatal\n");
	else if (node->size != 2)
		ft_putstr_fd(2, "error: cd: bad arguments\n");
	else if (chdir(node->argv[1]) == -1)
	{
		ft_putstr_fd(2, "error: cd: cannot change directory to");
		ft_putstr_fd(2, node->argv[1]);
		ft_putstr_fd(2, "\n");
	}
}

void	do_cd(t_node *node)
{
	if (!node)	exit_fatal();
	if (node->size != 2)	exit_cd_args();
	if (chdir(node->argv[1]) == -1) exit_cd_bad(node->argv[1]);
}

int		do_pipe(t_node *node, int read_fd, char **envp)
{
	int pipe_fd[2];
	if (pipe(pipe_fd) < 0) exit_fatal();
	pid_t pid = fork();
	if (pid < 0) exit_fatal();
	else if (pid == 0)
	{
		// pipe setting
		close(pipe_fd[0]);
		if (read_fd != STDIN_FILENO)
		{
			dup2(read_fd, STDIN_FILENO);
			close(read_fd);
		}
		if (node->next != NULL)
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		// execute
		if (!strcmp(node->argv[0], "cd"))
		{
			do_cd(node);
			exit (0);
		}
		else
		{
			if (execve(node->argv[0], node->argv, envp) < 0)
				exit_execve(node->argv[0]);
		}
	}
	else
	{
		int status;
		close(pipe_fd[1]);
		// 여기서도 read_fd를 닫아줘야 fd 누수가 발생하지 않는다.
		if (read_fd != STDIN_FILENO)
			close(read_fd);
		// 병렬 처리 하지 않아도 통과 된다.
		waitpid(pid, &status, 0);
	}
	return (pipe_fd[0]);
}




void	execute_lst(t_lst *lst, char **envp)
{
	t_node	*curr = lst->head;
	int		read_fd = STDIN_FILENO;

	// 파이프로 연결되지 않는 cd의 경우 error발생 시 error메세지와 함께
	// exit되어버리는 일이 발생하여 single_cd라는 함수를 만들었다.
	// single_cd는 fork되지 않기 때문에 exit하면 안 된다.
	if (lst->size == 1 && !strcmp(curr->argv[0], "cd"))
		do_single_cd(curr);
	else
	{
		while (curr)
		{
			read_fd = do_pipe(curr, read_fd, envp);
			curr = curr->next;
		}
		dup2(read_fd, STDIN_FILENO);
		close(read_fd);
	}
}

void	execute_cmds(t_tree *tree, char **envp)
{
	if (!tree) exit_fatal();
	t_lst	*curr = tree->head;
	while (curr)
	{
		execute_lst(curr, envp);
		curr = curr->next;
	}
}
