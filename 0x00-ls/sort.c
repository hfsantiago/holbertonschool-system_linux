#include "ls.h"
/**
 * sort - read the files and sort
 * Description: this function sort files
 * @files: double pointer to the arguments passed in the call
 * @mode: in which way is the info sorted
 * @folder: in which way is the info sorted
 * section header: the header of this function is ls.h
 * Return: a string with al the valid args
 */
char **sort(char **files, int mode, char *folder)
{
	lfile_s *lfile = NULL;

	lfile = to_list(files, folder);

	if (mode == 2)
	{
		reverse(&lfile);
	}
	if (mode == 3)
	{
		by_time(&lfile);
		reverse(&lfile);
	}
	if (mode == 4)
	{
		by_size(&lfile);
		reverse(&lfile);
	}
	files = to_array(&lfile);

	free_list(&lfile);
	return (files);
}
/**
 * reverse - this function convert a list to a doble pointer
 * @head: the head of list
 * Description: this converts list to a doble pointer.
 * section header: the header of this function is ls.h
 * Return: the doble pointer.
 **/
void reverse(lfile_s **head)
{
	lfile_s *temp = NULL;
	lfile_s *current = *head;

	while (current != NULL)
	{
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	if (temp != NULL)
		*head = temp->prev;
}
/**
 * by_size - insertion sort algorithm
 * Description: insertion sort algorithm
 * @list: list
 * Return: void
 */
void by_size(lfile_s **list)
{
	lfile_s *aux, *tail, *head, *swap_1, *swap_2, *aux_1, *aux_2;

	if (list == NULL || *list == NULL)
		return;
	head = *list;
	while (head != NULL && head->next != NULL)
	{
		if (head->size > head->next->size)
		{
			swap_1 = head, swap_2 = head->next;
			aux_1 = swap_1->prev, aux_2 = swap_2->next;
			if (aux_1 != NULL)
				aux_1->next = swap_2;
			else
				*list = swap_2;
			aux_2 != NULL ? aux_2->prev = swap_1 : aux_2;
			swap_2->prev = aux_1, swap_1->next = aux_2;
			swap_2->next = swap_1, swap_1->prev = swap_2;
			tail = head, head = head->prev;
			while (head && head->prev)
			{ aux = head;
				if (aux->size < aux->prev->size)
				{
					swap_1 = aux->prev, swap_2 = aux;
					aux_1 = swap_1->prev, aux_2 = swap_2->next;
					if (aux_1 != NULL)
						aux_1->next = swap_2;
					else
						*list = swap_2;
					aux_2 != NULL ? aux_2->prev = swap_1 : aux_2;
					swap_2->prev = aux_1, swap_1->next = aux_2;
					swap_2->next = swap_1, swap_1->prev = swap_2;
				}
				else
					break;
			} head = tail;
		} else
			head = head->next;
	}
}
/**
 * by_time - insertion sort algorithm
 * Description: insertion sort algorithm
 * @list: list
 * Return: void
 */
void by_time(lfile_s **list)
{
	lfile_s *aux, *tail, *head, *swap_1, *swap_2, *aux_1, *aux_2;

	if (list == NULL || *list == NULL)
		return;
	head = *list;
	while (head != NULL && head->next != NULL)
	{
		if (head->time > head->next->time)
		{
			swap_1 = head, swap_2 = head->next;
			aux_1 = swap_1->prev, aux_2 = swap_2->next;
			if (aux_1 != NULL)
				aux_1->next = swap_2;
			else
				*list = swap_2;
			aux_2 != NULL ? aux_2->prev = swap_1 : aux_2;
			swap_2->prev = aux_1, swap_1->next = aux_2;
			swap_2->next = swap_1, swap_1->prev = swap_2;
			tail = head, head = head->prev;
			while (head && head->prev)
			{ aux = head;
				if (aux->time < aux->prev->time)
				{
					swap_1 = aux->prev, swap_2 = aux;
					aux_1 = swap_1->prev, aux_2 = swap_2->next;
					if (aux_1 != NULL)
						aux_1->next = swap_2;
					else
						*list = swap_2;
					aux_2 != NULL ? aux_2->prev = swap_1 : aux_2;
					swap_2->prev = aux_1, swap_1->next = aux_2;
					swap_2->next = swap_1, swap_1->prev = swap_2;
				}
				else
					break;
			} head = tail;
		} else
			head = head->next;
	}
}
