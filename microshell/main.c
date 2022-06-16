#include "microshell.h"

int main(int argc, char **argv)
{
	t_tree	*tree;

	if (argc < 2)
		return (0);
	tree = parse_args(argv + 1);
	execute_commands(tree);
	free_tree(tree);
	return (0);
}
