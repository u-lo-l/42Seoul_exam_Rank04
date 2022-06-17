#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

/*==========DATA==========*/
typedef struct	s_node
{
	char			**argv;
	int				size;
	struct s_node	*next;
}	t_node;

typedef struct s_lst
{
	t_node			*head;
	t_node			*tail;
	int				size;
	struct s_lst	*next;
}	t_lst;

typedef struct s_tree
{
	t_lst	*head;
	t_lst	*tail;
}	t_tree;

/*==========EXIT==========*/
void	exit_fatal(void);
void	exit_execve(char *str);
void	exit_cd_args(void);
void	exit_cd_bad(char *str);
/*==========UTILS=========*/
void	*ft_calloc(int cnt, int len);
int		ft_strlen(char *str);
int		ft_putstr_fd(int fd, char *str);
char	*ft_strdup(char *str);

t_node	*create_node(char **argv, int size);
void	free_node(t_node *node);

int		add_node_to_lst(t_lst *lst, t_node *node);
void	free_lst(t_lst *lst);

int		add_lst_to_tree(t_tree *tree, t_lst *lst);
void	*free_tree(t_tree *tree);

/*=========PARSER=========*/
int		count_args(char **argv);
t_tree	*parse_commands(char **argv);
/*=========EXECUTE========*/
void	execute_cmds(t_tree *tree, char **envp);
/*==========MAIN==========*/
int main(int argc, char **argv, char **envp);
#endif
