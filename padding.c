#include "ft_ls.h"

int 	ft_find_hard_links_padding(t_file **head)
{
	int 	size;
	int 	max;
	t_file	*tmp;

	max = 0;
	tmp = *head;
	tmp = tmp->next;
	while (tmp)
	{	
		size = ft_nbrlen(tmp->hard_links, 10);
		if (size > max)
			max = size;
		tmp = tmp->next;
	}
	return (max);
}

int 	ft_find_uid_padding(t_file **head)
{
	int 	size;
	int 	max;
	t_file	*tmp;

	max = 0;
	tmp = *head;
	tmp = tmp->next;
	while (tmp)
	{	
		size = ft_strlen(tmp->uid);
		if (size > max)
			max = size;
		tmp = tmp->next;
	}
	return (max);
}


int 	ft_find_gid_padding(t_file **head)
{
	int 	size;
	int 	max;
	t_file	*tmp;

	max = 0;
	tmp = *head;
	tmp = tmp->next;
	while (tmp)
	{	
		size = ft_strlen(tmp->gid);
		if (size > max)
			max = size;
		tmp = tmp->next;
	}
	return (max);
}

int 	ft_find_size_in_bytes_padding(t_file **head)
{
	int 	size;
	int 	max;
	t_file	*tmp;

	max = 0;
	tmp = *head;
	tmp = tmp->next;
	while (tmp)
	{	
		size = ft_nbrlen(tmp->size_in_bytes, 10);
		if (size > max)
			max = size;
		tmp = tmp->next;
	}
	return (max);
}