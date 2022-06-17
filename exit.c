//EXIT
#include "microshell.h"

void	exit_fatal(void)
{
	ft_putstr_fd(2, "error: fatal\n");
	exit (1);
}

void	exit_execve(char *str)
{
	ft_putstr_fd(2, "error: execve: cannot execute ");
	ft_putstr_fd(2, str);
	ft_putstr_fd(2, "\n");
	exit (1);
}

void	exit_cd_args(void)
{
	ft_putstr_fd(2, "error: cd: bad arguments\n");
	exit (1);
}

void	exit_cd_bad(char *str)
{
	ft_putstr_fd(2, "error: cd: cannot find directory ");
	ft_putstr_fd(2, str);
	ft_putstr_fd(2, "\n");
	exit (1);
}
