#include "ft_ls.h"

int		ft_tolower(int c)
{
	return ((c >= 'A' && c <= 'Z') ? c + 32 : c);
}

char 	*ft_strtolower(char *str)
{
	char 	*copy_str;
	int 	i;

	i = -1;
	copy_str = (char *)malloc(sizeof(ft_strlen(str) + 1));
	while (str[++i])
		copy_str[i] = ft_tolower(str[i]);
	copy_str[i] = '\0';
	return (copy_str);
}

int 	ft_strcasecmp(char *str1, char *str2)
{
	int 	i;
	int 	res;
	char	*copy_str1;
	char	*copy_str2;

	i = 0;
	copy_str1 = ft_strtolower(str1);
	copy_str2 = ft_strtolower(str2);
	while (copy_str1[i] && (copy_str1[i] == copy_str2[i]))
		i++;
	res = copy_str1[i] - copy_str2[i];
	free(copy_str1);
	free(copy_str2);
	return (res);
}

void	ft_alpha_sort(char **array, int max_len, int size)
{
	int 	index;
	int 	other_index;
	char	tmp[max_len];

	index = 0;
	
	while (index < size + 1)
	{	
		other_index = index + 1;
		while (other_index < size)
		{	
			if (ft_strcasecmp(array[index], array[other_index]) > 0)
			{
				ft_strcpy(tmp, array[other_index]);
				ft_strcpy(array[other_index], array[index]);
				ft_strcpy(array[index], tmp);
			}
			other_index++;
		}
		index++;
	}
}

void	ft_reverse_alpha_sort(char **array, int max_len, int size)
{
	int 	index;
	int 	other_index;
	char	tmp[max_len];

	index = 0;
	while (index < size + 1)
	{	
		other_index = index + 1;
		while (other_index < size)
		{	
			if (ft_strcasecmp(array[index], array[other_index]) < 0)
			{
				ft_strcpy(tmp, array[other_index]);
				ft_strcpy(array[other_index], array[index]);
				ft_strcpy(array[index], tmp);
			}
			other_index++;
		}
		index++;
	}
}

// UNDER CONSTRUCTION

// void 	ft_node_swap(t_file *first, t_file *second)
// {

// }

// void	ft_time_sort(t_file *file)
// {
// 	t_file *current;
// 	t_file *previous;

// 	current = file;
// 	while (current->next)
// 	{
// 		if ((int)current->unix_time > (int)tmp->current->unix_time)
// 		{

// 		}
// 	}
// }