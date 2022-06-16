#include "microshell.h"

void	do_cd(t_args *arg)
{
	if (arg->size != 2)
		exit_cd_arg();
	else if (chdir(arg->argv[1]) == -1)
		exit_cd_bad(arg->argv[1]);
}
// 하....파이프.....
int		do_pipe(t_args *arg, int read_fd)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) < -1)
		exit_fatal();
	pid = fork();
	if (pid < 0)
		exit_fatal();
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		if (read_fd != STDIN_FILENO)
		{
			dup2(read_fd, STDIN_FILENO);
			close(read_fd);
		}
		if (arg->next != NULL)
			dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		if (strcmp(arg->argv[0], "cd") == 0)
		{
			do_cd(arg);
			exit(0);
		}
		else if (execve(arg->argv[0], arg->argv, NULL) < 0)
			exit_execve(arg->argv[0]);
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
	}
	return (pipe_fd[0]);
}
// lst로 연결된 명령어들은 pipe로 연결되어있다.
// 만약 명령어가 하나이고 그 명령어가 cd라면 fork하지 않고 실행한다.
void 	execute_lst(t_arglst *lst)
{
	t_args	*curr;
	int		read_fd;
	curr = lst->head;
	read_fd = STDIN_FILENO;
	if (lst->count == 1 && !strcmp(curr->argv[0], "cd"))
		do_cd(curr);
	else
	{
		while (curr)
		{
			read_fd = do_pipe(curr, read_fd);
			curr = curr->next;
		}	
		dup2(read_fd, 0);
		close(read_fd);
	}
}
// ;로 구분된 명령어 한 줄을 실행한다.(파이프가 포함될 수 있다.)
void	execute_commands(t_tree *tree)
{
	t_arglst *curr = tree->head;
	int		read_fd = 0;
	while (curr)
	{
		execute_lst(curr);
		curr  = curr->next;
	}
	close(read_fd);
}
