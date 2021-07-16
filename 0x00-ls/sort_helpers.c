#include "ls.h"
/**
 * to_list - this function creat a list from **pointer
 * @files: the double pointer to convert
 * @folder: the double pointer to convert
 * Description: this funtion create a list from a double pointer
 * section header: the header of this function is ls.h
 * Return: return the list.
 **/
lfile_s *to_list(char **files, char *folder)
{
	int i;
	lfile_s *lfile;
	struct stat file;
	char buffer[48];

	lfile = NULL;
	for (i = 0; files[i] != NULL; i++)
	{
		sprintf(buffer, "%s/%s", folder, files[i]);
		if (lstat(buffer, &file) == -1)
		{
			perror("lstat");
			exit(EXIT_FAILURE);
		}
		add_node(&lfile, files[i], file);
		free(files[i]);
	}
	free(files);
	return (lfile);

}
/**
 * to_array - this function convert a list to a doble pointer
 * @head: the head of list
 * Description: this converts list to a doble pointer.
 * section header: the header of this function is ls.h
 * Return: the doble pointer.
 **/
char **to_array(lfile_s **head)
{
	int i;
	lfile_s *h = *head;
	char **files;

	for (i = 0; h; i++)
		h = h->next;
	files = _calloc(i + 1, sizeof(char *));
	h = *head;
	for (i = 0; h; i++, h = h->next)
		files[i] = _strdup(h->var);
	return (files);
}
/**
 * _atoi - this function converts a string to integer
(* a blank line
 *@s: the string for convert to integer
* Description: this funtion converts a string to integer)?
(* section header: the header of this function is holberton.h)*
* Return: this funtion returns the result
*/
unsigned long int _atoi(char *s)
{
	unsigned long int counter;
	unsigned long int number;

	counter = 0;
	number = 0;

	while ((s[counter] >= '0') && (s[counter] <= '9'))
	{
		number = number * 10 + (s[counter] - '0');
		counter++;
	}
	return (number);
}
/**
 * _index - read the argv and select the valid args
 * Description: this function validates the argv and return the valid arguments
 * @valid: this argument contains the number of args passed in the call
 * @arg: double pointer to the arguments passed in the call
 * section header: the header of this function is ls.h
 * Return: true if the arg is valid, otherwise false
 */
int _index(char *valid, char arg)
{
	int i;

	for (i = 0; i < _strlen(valid); i++)
	{
		if (valid[i] == arg)
			return (i);
	}
	return (-1);
}
/**
 * select_sort - read the argv and select the valid args
 * Description: this function validates the argv and return the valid arguments
 * @args: double pointer to the arguments passed in the call
 * section header: the header of this function is ls.h
 * Return: true if the arg is valid, otherwise false
 */
char select_sort(char *args)
{
	if (include(args, 't'))
	{
		if (include(args, 'S'))
		{
			if (_index(args, 'S') > _index(args, 't'))
				;
			else
				return ('t');
		}
		else
			return ('t');
	}
	if (include(args, 'S'))
	{
		if (include(args, 't'))
		{
			if (_index(args, 't') > _index(args, 'S'))
				;
			else
				return ('S');
		}
		else
			return ('S');
	}
	return ('\0');
}