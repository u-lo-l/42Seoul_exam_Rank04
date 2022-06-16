#include "microshell.h"

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strdup(char *str)
{
	char	*dup;
	int		size = ft_strlen(str) + 1;
	dup = malloc(sizeof(char) * size);
	if (!dup) exit_fatal();
	int i = -1;
	while (++i < size)
		dup[i] = str[i];
	return (dup);
}

t_args	*create_args(char **argv, int size)
{
	t_args	*new = malloc(sizeof(t_args));
	if (!new)	exit_fatal();
	new->argv = malloc(sizeof(char *) * size + 1);
	if (new->argv == NULL)	exit_fatal();
	new->pipe = 0;
	new->next = NULL;
	new->size = size;
	int i = 0;
	for (; i < size ; i++)
		new->argv[i] = ft_strdup(argv[i]);
	new->argv[i] = NULL;
	return (new);
}

void	free_args(t_args *arg)
{
	if (!arg)
	{
		int i = 0;
		while (arg->argv[i])
		{
			free(arg->argv[i]);
			i++;
		}
	}
	free (arg);
}

void add_arg_to_lst(t_arglst *lst, t_args *arg)
{
	if (lst->head == NULL)
		lst->head = arg;
	if (lst->tail != NULL)
		lst->tail->next = arg;
	lst->tail = arg;
	lst->count++;
}

void	free_arglst(t_arglst *lst)
{
	t_args	*curr = lst->head;
	t_args	*next;
	while (curr)
	{
		next = curr->next;
		free_args(curr);
		curr = next;
	}
	free(lst);
}

void	add_lst_to_tree(t_tree *tree, t_arglst *lst)
{
	if (tree->head == NULL)
		tree->head = lst;
	if (tree->tail != NULL)
		tree->tail->next = lst;
	tree->tail = lst;
	tree->count++;
}

void	free_tree(t_tree *tree)
{
	t_arglst *curr = tree->head;
	t_arglst *next;
	while (curr)
	{
		next = curr->next;
		free_arglst(curr);
		curr = next;
	}
	free (tree);
}

void	print_args(t_args *arg)
{
	int i = 0;
	while (arg->argv[i])
		dprintf(2, "%s", arg->argv[i++]);
}

void	print_arglst(t_arglst *lst)
{
	t_args	*args = lst->head;
	dprintf(2, "lst c:%d |", lst->count);
	while (args)
	{
		dprintf(2, " <");
		print_args(args);
		dprintf(2, ">");
		args = args->next;
	}
}

void	print_tree(t_tree *tree)
{
	t_arglst *curr = tree->head;
	dprintf(2, "=======tree========\n");
	while (curr)
	{
		print_arglst(curr);
		dprintf(2, "\n");
		curr = curr->next;
	}
}
