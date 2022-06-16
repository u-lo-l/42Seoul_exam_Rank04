#include "microshell.h"

int	count_args(char **argv)
{
	int i = 0;
	if (!argv)	return (-1);
	while (argv[i])
	{
		if (!strcmp(argv[i], ";") || !strcmp(argv[i], "|"))
			break;
		i++;
	}
	return (i);
}

t_tree	*parse_args(char **argv)
{
	t_tree	*tree = malloc(sizeof(t_tree));
	tree->count = 0;
	tree->head = malloc(sizeof(t_arglst));
	tree->tail = tree->head;
	tree->tail->head = NULL;
	tree->tail->tail = NULL;
	tree->tail->next = NULL;
	tree->tail->count = 0;
	int i = 0;
	while (argv[i])
	{
		if (!strcmp(argv[i], ";"))
		{
			t_arglst *newlst = malloc(sizeof(t_arglst));
			newlst->head = NULL;
			newlst->tail = NULL;
			newlst->next = NULL;
			newlst->count = 0;
			add_lst_to_tree(tree, newlst);
			i++;
		}
		else if (!strcmp(argv[i], "|"))
			i++;
		else
		{
			int cnt = count_args(argv + i);
			t_args *node = create_args(argv + i, cnt);
			add_arg_to_lst(tree->tail, node);
			i += cnt;
		}
	}
	return (tree);
}
