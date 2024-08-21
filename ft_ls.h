#ifndef FT_LS
# define FT_LS
# define BLUE  "\x1b[1;34m"
# define GREEN "\x1b[1;32m"
# define RESET "\x1b[0m"
# define CYAN "\x1b[1;36m"

#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

typedef	struct 		s_file
{
	char			type_and_perm[10];
	char			*symlink_points_to;
	int				hard_links;
	char			*uid;
	char			*gid;
	int				size_in_bytes;
	int 			blocks_allocated;
	char			*mtime;
	time_t 			unix_time;
	char			*file_name;
	struct s_file	*next;
}					t_file;

typedef struct 		s_input
{
	int 			long_listing;
	int 			recursive;
	int  			all;
	int 			reverse;
	int 			mtime;
	int 			string;
	int 			error;
	int 			basic;
}					t_input;

void				ft_putnbr(int n);
void				ft_putstr(char *str);
void				ft_putchar(char c);
char				*ft_format_time(char *ctime_return);
int					ft_nbrlen(int nbr, int base);
t_file				*ft_create_file(char *file_name);
int 				ft_strlen(char *str);
void				ft_print_file_list(t_file *file, int hard_links_max, int uid_max, int gid_max, int size_in_bytes_max);
void				ft_ls_lstapnd(t_file **head, t_file *new);
void				ft_free_list(t_file **head);
int 				ft_find_hard_links_padding(t_file **head);
int 				ft_find_uid_padding(t_file **head);
int 				ft_find_gid_padding(t_file **head);
int 				ft_find_size_in_bytes_padding(t_file **head);
void				ft_print_list(t_file *elem, char flag, int max_len);
void				ft_print_default(t_file *file, int max_len);
int 				ft_sum_blocks_allocated(t_file **head);
char				*ft_strcpy(char *dst, char *src);
int					ft_tolower(int c);
char 				*ft_strtolower(char *str);
int 				ft_strcasecmp(char *str1, char *str2);
void				ft_alpha_sort(char **array, int max_len, int size);
void				ft_reverse_alpha_sort(char **array, int max_len, int size);
int 				ft_check_error(char *file_name);
t_input				*ft_parse_input(int argc, char **argv);
char				ft_find_invalid_option(char **argv);
int 				ft_count_non_option_strings(char **argv);
int					ft_do_the_thing(int argc, char **argv);

#endif