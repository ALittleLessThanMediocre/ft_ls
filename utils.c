#include "ft_ls.h"

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		if(1 == write(1, "-2147483648", 11))
			{;}
	}
	else
	{
		if (n < 0)
		{
			if(1 == write(1, "-", 1))
				{;}
			n *= -1;
		}
		if (n > 9)
			ft_putnbr(n / 10);
		n = (n % 10) + 48;
		if(1 == write(1, &n, 1))
			{;}
	}
}

void	ft_putstr(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len -= -1;
	if(1 == write(1, str, len))
		{;}
}

void	ft_putchar(char c)
{
	if(1 == write(1, &c, 1))
		{;}
}

int		ft_nbrlen(int nbr, int base)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0 && base == 10)
		len++;
	while (nbr)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

int 	ft_strlen(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len -= -1;
	return (len);
}

char	*ft_strcpy(char *dst, char *src)
{
	int i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

void	ft_ls_lstapnd(t_file **head, t_file *new)
{
	t_file *tmp;

	tmp = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_free_list(t_file **head)
{
	t_file	*tmp;

	tmp = *head;
	while (tmp->next)
	{
		free(tmp);
		tmp = tmp->next;
	}
	*head = NULL;
}