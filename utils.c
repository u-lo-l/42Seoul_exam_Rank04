//UTILS
#include "microshell.h"

void	*ft_calloc(int cnt, int size)
{
	void *mem = malloc(size * cnt);
	if (mem)
	{
		int i = 0;
		while (i < size * cnt)
			((char *)mem)[i++] = 0;
	}
	return (mem);
}

int		ft_strlen(char *str)
{
	if (!str)	return (-1);
	int	len = 0;
	while (str[len])
		len++;
	return (len);
}

int		ft_putstr_fd(int fd, char *str)
{
	int i = -1;
	while (str[++i])
		write(fd, str + i, 1);
	return (i);
}

char	*ft_strdup(char *str)
{
	int size = ft_strlen(str) + 1;
	char *dup = malloc(size);
	int i = -1;
	while (++i < size)
		dup[i] = str[i];
	return (dup);	
}

static void	free_argv(char **argv)
{
	int i = 0;
	if (!argv)	return;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

t_node	*create_node(char **argv, int size)
{
	t_node	*node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->size = size;
	node->next = NULL;
	node->argv = ft_calloc(size + 1, sizeof(char *));
	if (!node->argv)
	{
		free (node);
		return (NULL);
	}
	int i = 0;
	while (i < size)
	{
		node->argv[i] = ft_strdup(argv[i]);
		if (node->argv[i] == NULL)
		{
			free_argv(argv);
			return (NULL);
		}
		i++;
	}
	return (node);
}

void	free_node(t_node *node)
{
	if (node)
		free_argv(node->argv);
	free (node);
}

int		add_node_to_lst(t_lst *lst, t_node *node)
{
	if (!lst || !node) return(0);
	if (lst->head == NULL)
		lst->head = node;
	if (lst->tail != NULL)
		lst->tail->next = node;
	lst->tail = node;
	lst->size++;
	return (1);
}

void	free_lst(t_lst *lst)
{
	if (!lst) return ;
	t_node *curr = lst->head;
	t_node *next;
	while (curr)
	{
		next = curr->next;
		free_node(curr);
		curr = next;
	}
	free (lst);
}

int		add_lst_to_tree(t_tree *tree, t_lst *lst)
{
	if (!tree || !lst)	return (0);
	if (tree->head == NULL)
		tree->head = lst;
	if (tree->tail != NULL)
		tree->tail->next = lst;
	tree->tail = lst;
	return (1);
}

void	*free_tree(t_tree *tree)
{
	if (!tree) return (NULL);
	t_lst	*curr = tree->head;
	t_lst	*next;
	while (curr)
	{
		next = curr->next;
		free_lst(curr);
		curr = next;
	}
	free (tree);
	return (NULL);
}
