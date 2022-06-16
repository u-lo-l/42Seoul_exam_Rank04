#include "microshell.h"

void	exit_fatal()
{
	write(2, "error: fatal\n", ft_strlen("error: fatal\n"));
	exit (1);
}

void	exit_execve(char *str)
{
	write(2, "error : execve ", ft_strlen("error : execve "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit (1);
}

void exit_cd_arg()
{
	write(2, "error : cd : bad args\n", \
			ft_strlen("error : cd : bad args\n"));
	exit (1);
}

void exit_cd_bad(char *str)
{
	write(2, "error : cd ", ft_strlen("error : cd "));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit (1);
}
