//MAIN
#include "microshell.h"

#include <stdio.h>
/*static void print_node(t_node *node)
{
	if (!node)	return ;
	dprintf(2, "<");
	for (int i = 0 ; node->argv[i]; i++)
	{
		dprintf(2, "%s", node->argv[i]);
		if (node->argv[i + 1])
			dprintf(2, " ");
	}
	dprintf(2, ">");	
}

static void	print_lst(t_lst *lst)
{
	if (!lst) return ;
	dprintf(2, "lst size %d | ", lst->size);
	t_node *curr = lst->head;
	while (curr)
	{
		print_node(curr);
		dprintf(2, " ");
		curr = curr->next;
	}
}

static void print_tree(t_tree *tree)
{
	if (!tree)	return ;
	dprintf(2, "======tree======\n");
	t_lst	*curr = tree->head;
	while (curr)
	{
		print_lst(curr);
		dprintf(2, "\n");
		curr = curr->next;
	}
}

*/
int main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return (0);
	t_tree	*commands = parse_commands(argv + 1);
//	print_tree(commands);
	execute_cmds(commands, envp);
	free_tree(commands);
	//system("leaksa.out");
}
