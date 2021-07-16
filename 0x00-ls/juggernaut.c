#include "ls.h"
/**
 * juggernaut - read the argv and select the folders
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
char **juggernaut(int argc, char **argv, int *ret,
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
