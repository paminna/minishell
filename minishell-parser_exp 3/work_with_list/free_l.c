#include "../mini.h"

static void	free_element(t_list_env	*tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

int	delete_element_from_list(t_list_env **list, char *key)
{
	t_list_env	*tmp;
	t_list_env	*prev;
	t_list_env	*next;
	int			len;

	if (!list || !key)
		return (1);
	len = ft_strlen(key);
	tmp = *list;
	while (tmp != NULL)
	{
		prev = tmp->previous;
		next = tmp->next;
		if (!ft_strncmp(tmp->key, key, len + 1))
		{
			if (prev)
				prev->next = tmp->next;
			if (next)
				next->previous = tmp->previous;
			free_element (tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_cntlear(t_list **lst, void (*del_f)(void *))
{
	t_list	*temp_lst;
	t_list	*to_del_node;

	if ((!lst && !(*lst) && !del_f) || !lst || !(*lst) || !del_f)
		return ;
	temp_lst = *lst;
	while (temp_lst)
	{
		if (temp_lst->content)
			del_f(temp_lst->content);
		to_del_node = temp_lst;
		temp_lst = temp_lst->next;
		free(to_del_node);
	}
	*lst = NULL;
}

void	clear_list(t_cnt *cnt)
{
	ft_cntlear(&cnt->list, free);
	cnt->count = 0;
}