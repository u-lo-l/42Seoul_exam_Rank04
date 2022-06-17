//PARSER
#include "microshell.h"

int		count_args(char **argv)
{
	if (argv == NULL)	return (-1);
	int i = 0;
	while (argv[i])
	{
		if (!strcmp(argv[i], "|") || !strcmp(argv[i], ";"))
			break ;
		i++;
	}
	return (i);
}

t_tree	*parse_commands(char **argv)
{
	// Initiate 
	t_tree	*commands = ft_calloc(1, sizeof(t_tree));
	if (!commands)	return (NULL);

	commands->head = ft_calloc(1, sizeof(t_lst));
	if (!commands->head)
		return (free_tree(commands));
	commands->tail = commands->head;
	
	// Parse
	int i = 0;
	while (argv[i])
	{
		if (!strcmp(argv[i], ";"))
		{
			t_lst *emptylst = calloc(1, sizeof(t_lst));
			if (!emptylst)
				return (free_tree(commands));
			add_lst_to_tree(commands, emptylst);
			i++;
		}
		else if (!strcmp(argv[i], "|"))
			i++;
		else
		{
			int argc = count_args(argv + i);
			t_node	*node = create_node(argv + i, argc);
			if (!node)
				return (free_tree(commands));
			add_node_to_lst(commands->tail, node);
			i += argc;
		}
	}
	return (commands);
}
