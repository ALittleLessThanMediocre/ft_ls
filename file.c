#include "ft_ls.h"

char	*ft_format_time(char *ctime_return)
{
	char	*ret;
	int 	len;
	int 	colon_count;
	int 	i;
	int 	size;

	size = 0;
	len = 0;
	colon_count = 0;
	i = 0;
	while (ctime_return[len] != ' ')
		len -= -1;
	len++;
	while (ctime_return[size])
		size -= -1;
	ret = (char *)malloc(size - 8);
	while (ctime_return[len])
	{
		if (ctime_return[len] == ':')
			colon_count++;
		if (ctime_return[len] == ':' && colon_count == 2)
			break;
		ret[i++] = ctime_return[len++];
	}
	ret[i] = '\0';
	return (ret);
}

t_file 	*ft_create_file(char *file_name)
{
	t_file			*new_file;
	struct stat 	sb;
	struct passwd	*pwd;
	struct group	*grp;
	time_t			time;

	new_file = (t_file*)malloc(sizeof(t_file));
	lstat(file_name, &sb);
	
	if (S_ISDIR(sb.st_mode))
		new_file->type_and_perm[0] = 100;
	else if (S_ISLNK(sb.st_mode))
		new_file->type_and_perm[0] = 108;
	else
		new_file->type_and_perm[0] = 45;
	new_file->type_and_perm[1] = sb.st_mode & S_IRUSR ? 114 : 45;
	new_file->type_and_perm[2] = sb.st_mode & S_IWUSR ? 119 : 45;
	new_file->type_and_perm[3] = sb.st_mode & S_IXUSR ? 120 : 45;
	new_file->type_and_perm[4] = sb.st_mode & S_IRGRP ? 114 : 45;
	new_file->type_and_perm[5] = sb.st_mode & S_IWGRP ? 119 : 45;
	new_file->type_and_perm[6] = sb.st_mode & S_IXGRP ? 119 : 45;
	new_file->type_and_perm[7] = sb.st_mode & S_IROTH ? 114 : 45;
	new_file->type_and_perm[8] = sb.st_mode & S_IWOTH ? 119 : 45;
	new_file->type_and_perm[9] = sb.st_mode & S_IXOTH ? 120 : 45;

	new_file->hard_links = sb.st_nlink;

	pwd = getpwuid(sb.st_uid);
	new_file->uid = pwd->pw_name;

	grp = getgrgid(sb.st_gid);
	new_file->gid = grp->gr_name;

	new_file->size_in_bytes = sb.st_size;

	new_file->blocks_allocated = sb.st_blocks;

	time = sb.st_mtime;
	new_file->mtime = ft_format_time(ctime(&time));

	new_file->unix_time = time;

	new_file->file_name = file_name;

	new_file->next = NULL;

	return (new_file);
}

int 	ft_check_error(char *file_name)
{
	char			*no_access;
	char			*non_existant;
	struct stat 	sb;

	no_access = "EACCES";
	non_existant = "ENOENT";

	if (lstat(file_name, &sb) == -1)
	{
		if (strerror(errno) == no_access)
			return (-1);
		
		if (strerror(errno) == non_existant)
			return (-2);
	}
	return (0);
}

void	ft_print_file_list(t_file *file, int hard_links_max, int uid_max, int gid_max, int size_in_bytes_max)
{
	int 	padding;
	char	buff[PATH_MAX];
	int 	bytes_read;

	ft_putchar(file->type_and_perm[0]);
	ft_putchar(file->type_and_perm[1]);
	ft_putchar(file->type_and_perm[2]);
	ft_putchar(file->type_and_perm[3]);
	ft_putchar(file->type_and_perm[4]);
	ft_putchar(file->type_and_perm[5]);
	ft_putchar(file->type_and_perm[6]);
	ft_putchar(file->type_and_perm[7]);
	ft_putchar(file->type_and_perm[8]);
	ft_putchar(file->type_and_perm[9]);
	ft_putchar(32);

	if (ft_nbrlen(file->hard_links, 10) < hard_links_max)
	{
		padding = hard_links_max - ft_nbrlen(file->hard_links, 10);
		while (padding--)
			ft_putchar(32);
		ft_putnbr(file->hard_links);
	}
	else
		ft_putnbr(file->hard_links);

	ft_putchar(32);

	if (ft_strlen(file->uid) < uid_max)
	{
		padding = uid_max - ft_strlen(file->uid);
		while (padding--)
			ft_putchar(32);
		ft_putstr(file->uid);
	}
	else
		ft_putstr(file->uid);

	ft_putchar(32);

	if (ft_strlen(file->gid) < gid_max)
	{
		padding = gid_max - ft_strlen(file->gid);
		while (padding--)
			ft_putchar(32);
		ft_putstr(file->gid);
	}
	else
		ft_putstr(file->gid);

	ft_putchar(32);

	if (ft_nbrlen(file->size_in_bytes, 10) < size_in_bytes_max)
	{
		padding = size_in_bytes_max - ft_nbrlen(file->size_in_bytes, 10);
		while (padding--)
			ft_putchar(32);
		ft_putnbr(file->size_in_bytes);
	}
	else
		ft_putnbr(file->size_in_bytes);

	ft_putchar(32);

	ft_putstr(file->mtime);
	ft_putchar(32);

	if (file->type_and_perm[0] == 100)
	{
		ft_putstr(BLUE);
		ft_putstr(file->file_name);
		ft_putstr(RESET);
	}
	else if (file->type_and_perm[3] == 120 && file->type_and_perm[0] != 108)
	{
		ft_putstr(GREEN);
		ft_putstr(file->file_name);
		ft_putstr(RESET);
	}
	else if (file->type_and_perm[0] == 108)
	{
		ft_putstr(CYAN);
		ft_putstr(file->file_name);
		ft_putstr(RESET);
	}
	else
		ft_putstr(file->file_name);

	if (file->type_and_perm[0] == 'l')
	{
		bytes_read = 0;
		if ((bytes_read = readlink(file->file_name, buff, sizeof(buff) - 1)) > 0)
			buff[bytes_read] = '\0';
		ft_putchar(32);
		ft_putstr("->");
		ft_putchar(32);
		ft_putstr(buff);
		ft_putchar(10);
	}
	else
		ft_putchar(10);
}

void	ft_print_default(t_file *file, int max_len)
{
	int 	padding;

	if (ft_strlen(file->file_name) < max_len)
	{
		if (file->type_and_perm[0] == 100)
		{
			ft_putstr(BLUE);
			ft_putstr(file->file_name);
			ft_putstr(RESET);
		}
		else if (file->type_and_perm[3] == 120 && file->type_and_perm[0] != 108)
		{
			ft_putstr(GREEN);
			ft_putstr(file->file_name);
			ft_putstr(RESET);
		}
		else if (file->type_and_perm[0] == 108)
		{
			ft_putstr(CYAN);
			ft_putstr(file->file_name);
			ft_putstr(RESET);
		}
		else
			ft_putstr(file->file_name);
		padding = max_len - ft_strlen(file->file_name);
		while (padding--)
			ft_putchar(32);
	}
	else
	{
		if (file->type_and_perm[0] == 100)
		{
			ft_putstr(BLUE);
			ft_putstr(file->file_name);
			ft_putstr(RESET);
		}
		else if (file->type_and_perm[3] == 120 && file->type_and_perm[0] != 108)
		{
			ft_putstr(GREEN);
			ft_putstr(file->file_name);
			ft_putstr(RESET);
		}
		else if (file->type_and_perm[0] == 108)
		{
			ft_putstr(CYAN);
			ft_putstr(file->file_name);
			ft_putstr(RESET);
		}
		else
		{
			ft_putstr(file->file_name);
			ft_putchar(32);
		}
	}
}

void	ft_print_list(t_file *elem, char flag, int max_len)
{
	t_file	*tmp;
	int 	hard_links_max;
	int 	uid_max;
	int 	gid_max;
	int 	size_in_bytes_max;
	int 	tab;

	if (flag == 'l')
	{
		tmp = elem;
		hard_links_max = ft_find_hard_links_padding(&tmp);
		tmp = elem;
		uid_max = ft_find_uid_padding(&tmp);
		tmp = elem;
		gid_max = ft_find_gid_padding(&tmp);
		tmp = elem;
		size_in_bytes_max = ft_find_size_in_bytes_padding(&tmp);
		tmp = elem;
		while (tmp)
		{
			ft_print_file_list(tmp, hard_links_max, uid_max, gid_max, size_in_bytes_max);
			tmp = tmp->next;
		}
	}
	else
	{
		tab = 0;
		tmp = elem;
		while (tmp)
		{
			ft_print_default(tmp, max_len);
			tab -= -1;
			if (tab > 3)
			{
				ft_putchar(10);
				tab = 0;
			}
			tmp = tmp->next;
		}
		ft_putchar(10);
	}
}

int 	ft_sum_blocks_allocated(t_file **head)
{
	int 	sum;
	t_file	*tmp;

	sum = 0;
	tmp = *head;
	tmp = tmp->next;
	while (tmp)
	{
		sum += tmp->blocks_allocated;
		tmp = tmp->next;
	}
	return (sum);
}

t_input	*ft_parse_input(int argc, char **argv)
{
	t_input	*options;
	int 	index;
	int 	other_index;

	options = (t_input*)malloc(sizeof(t_input));
	options->basic = 0;
	index = 1;
	other_index = 1;
	if (argc == 1)
	{
		options->long_listing = 0;
		options->recursive = 0;
		options->all = 0;
		options->reverse = 0;
		options->mtime = 0;
		options->string = 0;
		options->basic = 1;

		return (options);
	}
	else
	{
		while (argv[index])
		{
			if (argv[index][0] == '-')
			{
				while (argv[index][other_index])
				{
					argv[index][other_index] == 'l' ? options->long_listing = 1 : 0;
					argv[index][other_index] == 'R' ? options->recursive = 1 : 0;
					argv[index][other_index] == 'a' ? options->all = 1 : 0;
					argv[index][other_index] == 'r' ? options->reverse = 1 : 0;
					argv[index][other_index] == 't' ? options->mtime = 1 : 0;

					if (argv[index][other_index] != 'l' && argv[index][other_index] != 'R' && argv[index][other_index] != 'a' \
						 && argv[index][other_index] != 'r' && argv[index][other_index] != 't')
					{
						options->error = 1;
						return (options);
					}
					other_index++;
				}
			}
			else
				options->string = 1;
			other_index = 1;
			index++;
		}
		return (options);
	}
}

char	ft_find_invalid_option(char **argv)
{
	char	offending_character;
	int 	index;
	int 	other_index;

	offending_character = 0;
	index = 1;
	other_index = 1;
	while (argv[index])
	{
		if (argv[index][0] == '-')
		{
			while (argv[index][other_index])
			{
				if (argv[index][other_index] != 'l' && argv[index][other_index] != 'R' && argv[index][other_index] != 'a' \
					 && argv[index][other_index] != 'r' && argv[index][other_index] != 't')
				{
					offending_character = argv[index][other_index];
					return (offending_character);
				}
				other_index++;
			}
		}
		other_index = 1;
		index++;
	}
	return (offending_character);
}

int 	ft_count_non_option_strings(char **argv)
{
	int index;
	int count;

	index = 0;
	count = 0;
	while (argv[index])
	{
		if (argv[index][0] == '-' || argv[index][0] == '.')
			index -= -1;
		else
		{
			count -= -1;
			index -= -1;
		}
	}
	return (count);
}

int		ft_do_the_thing(int argc, char **argv)
{
	DIR				*current_dir;
	struct 	dirent	*files;
	int 			nbr_of_files;
	int 			index;
	char			**file_name_array;
	int 			max_len;
	t_file			*head;
	t_input			*input;
	char 			the_delinquent;
	int 			error_return;

	index = 0;
	nbr_of_files = 0;
	max_len = 0;
	head = NULL;
	error_return = 0;

	input = ft_parse_input(argc, argv);

	if (input->error)
	{
		the_delinquent = ft_find_invalid_option(argv);
		ft_putstr("ft_ls: invalid option -- '");
		ft_putchar(the_delinquent);
		ft_putstr("'\n");
		ft_putstr("Try 'ls --help' for more information.\n");
		
		return (0);
	}

	if (input->string)
	{
		nbr_of_files = ft_count_non_option_strings(argv);
		file_name_array = (char **)malloc(sizeof(char*) * nbr_of_files + 1);

		while (--argc)
		{
			++argv;
			if (*argv[0] != '-' && *argv[0] != '.')
			{
				file_name_array[index] = *argv;
				if (ft_strlen(*argv) > max_len)
					max_len = ft_strlen(*argv);
				index++;
			}
		}
		file_name_array[index] = '\0';
	}
	else
	{
		if (input->all)
		{

			current_dir = opendir(".");

			while ((files = readdir(current_dir)) != NULL)
				nbr_of_files -= -1;
			closedir(current_dir);

			file_name_array = (char **)malloc(sizeof(char*) * nbr_of_files + 1);

			current_dir = opendir(".");
			while ((files = readdir(current_dir)) != NULL)
			{	
				if (ft_strlen(files->d_name) > max_len)
					max_len = ft_strlen(files->d_name);
				file_name_array[index++] = files->d_name;
			}
			file_name_array[index] = '\0';
		}
		else
		{
			current_dir = opendir(".");

			while ((files = readdir(current_dir)) != NULL)
			{
				if (files->d_name[0] != '.')
					nbr_of_files -= -1;
			}
			closedir(current_dir);

			file_name_array = (char **)malloc(sizeof(char*) * nbr_of_files + 1);

			current_dir = opendir(".");
			while ((files = readdir(current_dir)) != NULL)
			{	
				if (files->d_name[0] != '.')
				{
					if (ft_strlen(files->d_name) > max_len)
						max_len = ft_strlen(files->d_name);
					file_name_array[index++] = files->d_name;
				}
			}
			file_name_array[index] = '\0';
		}
	}
	
	if (input->basic)
	{
		current_dir = opendir(".");
		ft_alpha_sort(file_name_array, max_len, nbr_of_files);
		index = 0;
		while (file_name_array[index])
		{
			t_file *file = ft_create_file(file_name_array[index]);
			ft_ls_lstapnd(&head, file);
			index++;
		}
		free(file_name_array);
		ft_print_list(head, '-', max_len);
		ft_free_list(&head);
		closedir(current_dir);

		return (0);
	}

	if (input->reverse)
	{

		if (input->long_listing)
		{
			current_dir = opendir(".");
			ft_reverse_alpha_sort(file_name_array, max_len, nbr_of_files);
			index = 0;
			while (file_name_array[index])
			{
				t_file *file = ft_create_file(file_name_array[index]);
				ft_ls_lstapnd(&head, file);
				index++;
			}
			free(file_name_array);
			ft_putstr("total ");
			ft_putnbr(ft_sum_blocks_allocated(&head));
			ft_putchar(10);
			ft_print_list(head, 'l', max_len);
			ft_free_list(&head);
			closedir(current_dir);

			return (0);
		}
		else
		{
			current_dir = opendir(".");
			ft_reverse_alpha_sort(file_name_array, max_len, nbr_of_files);
			index = 0;
			while (file_name_array[index])
			{
				t_file *file = ft_create_file(file_name_array[index]);
				ft_ls_lstapnd(&head, file);
				index++;
			}
			free(file_name_array);
			ft_print_list(head, '-', max_len);
			ft_free_list(&head);
			closedir(current_dir);

			return (0);
		}
	}
	else
	{
		ft_alpha_sort(file_name_array, max_len, nbr_of_files);

		if (input->long_listing)
		{
			current_dir = opendir(".");
			index = 0;
			while (file_name_array[index])
			{
				t_file *file = ft_create_file(file_name_array[index]);
				ft_ls_lstapnd(&head, file);
				index++;
			}
			free(file_name_array);
			ft_putstr("total ");
			ft_putnbr(ft_sum_blocks_allocated(&head));
			ft_putchar(10);
			ft_print_list(head, 'l', max_len);
			ft_free_list(&head);
			closedir(current_dir);

			return (0);
		}
		else
		{
			current_dir = opendir(".");
			index = 0;
			while (file_name_array[index])
			{
				error_return = ft_check_error(file_name_array[index]);
				if (error_return == -1)
				{
					free(file_name_array);
					if (head)
						ft_free_list(&head);
					ft_putstr("ft_ls: cannot open '");
					ft_putstr(file_name_array[index]);
					ft_putstr("': Permission denied\n");

					return (0);
				}
				if (error_return == -2)
				{
					free(file_name_array);
					if (head)
						ft_free_list(&head);
					ft_putstr("ft_ls: cannot access '");
					ft_putstr(file_name_array[index]);
					ft_putstr("' No such file or directory\n");

					return (0);
				}
				if (error_return == 0)
				{
					t_file *file = ft_create_file(file_name_array[index]);
					ft_ls_lstapnd(&head, file);
					index++;
				}
			}
			ft_print_list(head, '-', max_len);
			ft_free_list(&head);
			free(file_name_array);
			closedir(current_dir);

			return (0);
		}
	}
	return (0);
}