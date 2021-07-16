#include "ls.h"
/**
 * validate_args - read the argv and select the valid args
 * Description: this function validates the argv and return the valid arguments
 * @argv: double pointer to the arguments passed in the call
 * @errors: pointer to free in some cases
 * section header: the header of this function is ls.h
 * Return: a string with al the valid args
 */
char *validate_args(char **argv, char **errors)
{
	int i, j;
	char buff[120] = {'-', '\0'};
	char *args = NULL;
	char *valid_args = "1aAlrStR", str[2];

	for (i = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '-' &&  _strstr(argv[i], "--") == NULL)
		{
			for (j = 1; argv[i][j] != '\0'; j++)
				if (include(valid_args, argv[i][j]))
				{
					if (!include(buff, argv[i][j]))
						str[0] = argv[i][j], str[1] = '\0', _strcat(buff, str);
					continue;
				}
				else
				{
					fprintf(stderr,
					"hls: invalid option -- '%c'\nTry 'hls --help' for more information.\n",
					argv[i][j]);
					free(errors);
					exit(2);
				}
		}
		if (_strstr(argv[i], "---") != NULL)
		{
			fprintf(stderr,
			"hls: unrecognized option '---'\nTry 'hls --help' for more information.\n");
			free(errors), exit(2);
		}
	}
	if (_strlen(buff) != 0)
	{
		args = _strdup(buff);
		return (args);
	}
	return (NULL);
}
/**
 * validate_dir - read the argv and select the folders
 * Description: this function validates the argv and return the valid folders
 * @argc: this argument contains the number of args passed in the call
 * @argv: double pointer to the arguments passed in the call
 * @ret: is the value of return in normal cases 0 in error 2
 * @fcount: is the count of folders that ls recieves as an arg
 * @ficount: is the count of files that ls recieves as an arg
 * @errors: count of errors that occurs
 * @args: count of errors that occurs
 * section header: the header of this function is ls.h
 * Return: a double pointer that contains all the valid folders
 */
char **validate_dir(int argc, char **argv, int *ret,
					int *fcount, int *errors, int *ficount, char *args)
{
	char **folders = NULL, **files;
	int i = 0, j = 0, dash = 0, k = 0;
	struct stat file;

	files = _calloc(100, sizeof(*files));
	if (argc != 1)
	{
		folders = malloc(sizeof(*folders) * argc);
		if (folders == NULL)
			return (NULL);
		for (i = 1, j = 0; argv[i] != NULL; i++, j++)
		{
			if (lstat(argv[i], &file) == 0 && S_ISDIR(file.st_mode)
										&& !S_ISREG(file.st_mode))
				folders[j] = _strdup(argv[i]), (*fcount)++;
			else if (argv[i][0] == '-')
				j--, _strcmp(argv[i], "--") != 0 ? dash = 1 : 1;
			else if (lstat(argv[i], &file) == 0 && S_ISREG(file.st_mode))
				files[k] = _strdup(argv[i]), (*ficount)++, j--, k++;
			else
				fprintf(stderr,
						"hls: cannot access %s: No such file or directory\n",
						argv[i]), (*ret) = 2, (*errors)++, j--;
		}
	}
	 (*ficount) > 0 ? print_dir(files, args, ".") : 1;
	 (*ficount) > 0  && (*fcount) > 0 ? printf("\n") : 1;
	if (((*fcount) == 0 && (*errors) == 0 && (*ficount) == 0) ||
		(dash == 1 && ((*fcount) == 0 && (*errors) == 0 && (*ficount) == 0)))
	{
		free(folders), folders = malloc(sizeof(*folders));
		if (folders == NULL)
			return (NULL);
		folders[0] = _strdup("."), (*fcount)++;
	}
	if ((*ficount) == 0)
		free(files);
	return (folders);
}

/**
 * open_dir - open a dir
 * Description: this function validates the argv and try to open the folder
 * in case argv was empty open the execution folder
 * @folder: folder to open
 * section header: the header of this function is ls.h
 * Return: a valid directory
 */
DIR *open_dir(char *folder)
{
	DIR *dir;

	dir = opendir(folder);
	if (dir)
		return (dir);
	else
		return (NULL);

}
/**
 * read_dir - read the folder
 * Description: this function read a directory and print the content
 * @dir: directory to read
 * @folder: the name of the folder
 * @ret: is the value of return in normal cases 0 in error 2
 * @errors: a double pointer that stores the names of the folder with errors
 * section header: the header of this function is ls.h
 * Return: void
 */
char **read_dir(DIR *dir, char *folder, int *ret, char **errors)
{
	struct stat file;
	struct dirent *read;
	char **files = NULL;
	int i;

	if (lstat(folder, &file) == 0 && file.st_mode & S_IRUSR)
	{
		files = _calloc(100, sizeof(*files));
		for (i = 0; (read = readdir(dir)) != NULL; i++)
			files[i] = _strdup(read->d_name);
	}
	else
	{
		for (i = 0; *(errors + i); i++)
		{
		}
		*(errors + i) = _strdup(folder);
		*(ret) = 3;
	}
	if (files)
		files = sort(files, 1, folder);
	return (files);
}
/**
 * print_dir - print the folder
 * Description: this function print the content
 * @files: the files that the folder contains
 * @args: the arguments passed to ls to format the output
 * @folder: the folder that is print
 * section header: the header of this function is ls.h
 * Return: 0 in success
 */
int print_dir(char **files, char *args, char *folder)
{
	char *buffer;
	char sort_mode;

	buffer = _calloc(8192, sizeof(char));
	sort_mode = select_sort(args);
	if (sort_mode == 't')
		files = sort(files, 3, folder);
	if (sort_mode == 'S')
		files = sort(files, 4, folder);
	if (include(args, 'r'))
		files = sort(files, 2, folder);
	if (!include(args, 'a') && !include(args, 'A'))
		files = flag_a(files, folder);
	if (include(args, 'A') && !include(args, 'a'))
		files = flag_A(files, folder);
	if (include(args, '1') && !include(args, 'l'))
		flag_1(files, folder, &buffer);
	if (include(args, 'l'))
		flag_l(files, folder, &buffer);
	if (_strcmp(args, "-") == 0)
		without_flags(files, folder, &buffer);
	else if (include(args, 'a') || include(args, 'A')
			|| include(args, 'r') || include(args, 'S') || include(args, 't'))
	{
		if (include(args, 'l') || include(args, '1'))
			;
		else
			without_flags(files, folder, &buffer);

	}
	if (_strlen(buffer) > 0)
		printf("%s", buffer);
	if (!include(args, '1') && !include(args, 'l') && _strlen(buffer) > 0)
		printf("\n");
	free(buffer);
	return (0);
}
