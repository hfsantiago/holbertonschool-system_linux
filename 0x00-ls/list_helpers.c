#include "ls.h"
/**
 * add_node - add a new node to a list
 * a blank line
 * @head: the head of list
 * @str: the string to put in the new node
 * @file: info
 * Description: add a new node to a list
 * section header: the header of this function is hsh.h
 * Return: the head of the list.
 */
lfile_s *add_node(lfile_s **head, char *str, struct stat file)
{
	lfile_s *new;
	lfile_s *actual;

	actual = *head;
	new = malloc(sizeof(lfile_s));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->var = _strdup(str);
	new->time = parse_date(file);
	new->size = (long) file.st_size;
	if (actual == NULL)
	{
		new->prev = NULL;
		*head = new;
		return (new);
	}
	while (actual->next)
	{
		actual = actual->next;
	}
	actual->next = new;
	new->prev = actual;
	return (new);
}
/**
 * print_list - this function prints a list
 * @head: the head of list
 * Description: this function prints a list
 * section header: the header of this function is hsh.h
 * Return: the number of nodes
 **/
size_t print_list(lfile_s **head)
{
	int i;

	lfile_s *h = *head;

	for (i = 0; h ; i++)
	{
		if (h->var == NULL)
			printf("[0] (nil)\n");
		else
			printf("file -> {%s} size -> {%li} -> {%lu}\n", h->var, h->size, h->time);
		h = h->next;
	}
	printf("\n");
	return (i);
}
/**
 * free_list - free a list
 * @head: the head of list
 * Description: this function free a list.)?
 * section header: the header of this function is lists.h)*
 * Return: void, no return
 **/
void free_list(lfile_s **head)
{
	lfile_s *h;
	lfile_s *position, *next;


	h = *head;
	position = h;
	while (position != NULL)
	{
		next = position->next;
		free(position->var);
		free(position);
		position = next;
	}
	h = '\0';
}
/**
 * delete_node - thsi function delete a node
 * @head: the head of list
 * @index: the index to put the delete node
 * Description: this function delete a node
 * section header: the header of this function is hsh.h
 * Return: 1 in success -1 in failure
 **/
int delete_node(lfile_s **head, unsigned int index)
{
	lfile_s *actual, *next;
	unsigned int i;

	if (head == NULL || *head == NULL)
		return (-1);

	actual = *head;

	if (index == '\0')
	{
		*head = actual->next;
		free(actual);
		return (1);
	}

	for (i = 0; actual && i < index - 1; i++)
		actual = actual->next;

	if (actual == NULL || actual->next == NULL)
		return (-1);

	next = actual->next->next;
	free(actual->next->var);
	free(actual->next);
	actual->next = next;
	return (1);
}
