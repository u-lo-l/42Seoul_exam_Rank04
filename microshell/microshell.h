#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

//DATA
typedef struct args
{
	char		**argv;
	int			size;
	struct args *next;
}	t_args;

typedef struct arglst
{
	int				count;
	t_args			*head;
	t_args			*tail;
	struct arglst	*next;
}	t_arglst;

typedef struct tree
{
	int				count;
	t_arglst		*head;
	t_arglst		*tail;
}	t_tree;

// EXIT
void	exit_fatal();
void	exit_execve(char *str);
void	exit_cd_arg();
void	exit_cd_bad(char *str);

// UTILS
int		ft_strlen(char *);
char	*ft_strdup(char *);
t_args	*create_args(char **argv, int size);
void	free_args(t_args *args);
void	add_arg_to_lst(t_arglst *lst, t_args *arg);
void	free_arglst(t_arglst *lst);
void	add_lst_to_tree(t_tree *tree, t_arglst *lst);
void	free_tree(t_tree *tree);

void	print_args(t_args *arg);
void	print_arglst(t_arglst *lst);
void	print_tree(t_tree *tree);

// PARSING
int	count_args(char **argv);
t_tree	*parse_args(char **argv);
// EXECUTE
void	execute_commands(t_tree *tree);
