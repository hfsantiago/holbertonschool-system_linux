#ifndef LS_H
#define LS_H

#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include <grp.h>



/**
 * struct lfile_s - singly linked list
 * @str: variable
 * @size: variable
 * @time: variable
 * @next: points to the next node
 * @prev: points to the prev node
 * @var: enviroment variables.
 * Description: singly linked list node to store the env
 */
typedef struct lfile_s
{
	char *var;
	long int size;
	unsigned long int time;
	struct lfile_s *prev;
	struct lfile_s *next;
} lfile_s;

/* lib */
char *validate_args(char **argv, char **errors);
char **validate_dir(int argc, char **argv,
					int *ret, int *fcount, int *errors, int *ficount, char *args);
char **juggernaut(int argc, char **argv,
					int *ret, int *fcount, int *errors, int *ficount, char *args);
DIR *open_dir(char *folder);
char **read_dir(DIR *dir, char *folder, int *ret, char **errors);
int print_dir(char **files, char *args, char *folder);

/* utils */
bool include(char *valid, char arg);
char *permissions(struct stat file);
char *get_date(struct stat file);
long int parse_date(struct stat file);
int get_nodes(char **files, char *folder);


/* flags */

void flag_l(char **files, char *folder, char **buffer);
void flag_1(char **files, char *folder, char **buffer);
char **flag_a(char **files, char *folder);
char **flag_A(char **files, char *folder);
void without_flags(char **files, char *folder, char **buffer);



/* sorting */

char **sort(char **files, int mode, char *folder);



/* sorting helpers */
lfile_s *to_list(char **files, char *folder);
char **to_array(lfile_s **head);
void by_size(lfile_s **list);
void by_time(lfile_s **list);
void reverse(lfile_s **list);
int _index(char *valid, char arg);
char select_sort(char *args);

/* list helpers */

int delete_node(lfile_s **head, unsigned int index);
lfile_s *add_node(lfile_s **head, char *str, struct stat file);
void free_list(lfile_s **head);
size_t print_list(lfile_s **head);



/* memory helpers */
char *_memset(char *s, char b, unsigned int n);
void *_calloc(unsigned int nmemb, unsigned int size);


/* string helpers */

char *_strcat(char *dest, char *src);
int _strlen(char *s);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *_strstr(char *haystack, char *needle);
unsigned long int _atoi(char *s);


#endif /* LS_H */
