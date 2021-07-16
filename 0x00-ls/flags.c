#include "ls.h"
/**
 * flag_l - function to manage the "l" flag
 * Description: print in long format
 * @files: the files that the folder contains
 * @folder: the folder that is print
 * @vuffer: buffer
 * section header: the header of this function is ls.h
 * Return: void
 */
void flag_l(char **files, char *folder, char **vuffer)
{
	struct stat file;
	int i;
	char buffer[48];
	struct passwd *usr;
	struct group *grp;
	char *perm, *date;
	char buff[512];

	for (i = 0; files[i] != NULL; i++)
	{
		sprintf(buffer, "%s/%s", folder, files[i]);

		if (lstat(buffer, &file) == -1)
		{
			perror("lstat");
			exit(EXIT_FAILURE);
		}
		usr = getpwuid(file.st_uid);
		grp = getgrgid(file.st_gid);
		perm = permissions(file);
		date = get_date(file);
		sprintf(buff, "%s %ld %s %s %ld %s %s\n",
		perm,
		(long) file.st_nlink,
		usr->pw_name != NULL ? usr->pw_name : "",
		grp->gr_name != NULL ? grp->gr_name : "",
		(long) file.st_size,
		date,
		files[i]
		);
		free(files[i]);
		free(perm);
		free(date);
		_strcat(*(vuffer), buff);
	}
	free(files);
}
/**
 * flag_a - function to manage the "a" flag
 * Description: print hide things
 * @files: the files that the folder contains
 * @folder: the folder that is print
 * section header: the header of this function is ls.h
 * Return: void
 */
char **flag_a(char **files, char *folder)
{
	int i, j;
	char **buffer;
	(void) folder;

	buffer = _calloc(48, sizeof(*buffer));
	for (i = 0, j = 0; files[i] != NULL; i++)
	{
		if (files[i][0] != '.')
		{
			buffer[j] = _strdup(files[i]);
			j++;
		}


	free(files[i]);
	}
	free(files);
	return (buffer);
}
/**
 * flag_A - function to manage the "A" flag
 * Description: print hide things with exceptions
 * @files: the files that the folder contains
 * @folder: the folder that is print
 * section header: the header of this function is ls.h
 * Return: void
 */
char **flag_A(char **files, char *folder)
{
	int i, j;
	char **buffer;
	(void) folder;

	buffer = _calloc(48, sizeof(*buffer));
	for (i = 0, j = 0; files[i] != NULL; i++)
	{
		if (_strcmp(files[i], ".") != 0 && _strcmp(files[i], "..") != 0)
		{
			buffer[j] = _strdup(files[i]);
			j++;
		}
	free(files[i]);
	}
	free(files);
	return (buffer);
}
/**
 * flag_1 - function to manage the "1" flag
 * Description: print witn /n between each file
 * @files: the files that the folder contains
 * @folder: the folder that is print
 * @buffer: the print buffer
 * section header: the header of this function is ls.h
 * Return: void
 */
void flag_1(char **files, char *folder, char **buffer)
{
	int i;
	(void) folder;

	for (i = 0; files[i] != NULL; i++)
	{
		_strcat(*(buffer), files[i]);
		_strcat(*(buffer), "\n");
		free(files[i]);
	}
	free(files);
}
/**
 * without_flags - function to manage the normal print
 * Description: normal ls print
 * @files: the files that the folder contains
 * @folder: the folder that is print
 * @buffer: the print buffer
 * section header: the header of this function is ls.h
 * Return: void
 */
void without_flags(char **files, char *folder, char **buffer)
{
	int i;
	(void) folder;
	for (i = 0; files[i] != NULL; i++)
	{
		_strcat(*(buffer), files[i]);
		_strcat(*(buffer), "  ");
		free(files[i]);
	}
	free(files);
}
