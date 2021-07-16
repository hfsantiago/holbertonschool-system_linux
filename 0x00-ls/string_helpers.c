#include "ls.h"
/**
 * _strcat - this function concatenate two strings
 * @dest: the first string to be concatenated
 * @src: the second string to be concatenated
(* a blank line
* Description: this function concatenate two strings)?
(* section header: the header of this function is holberton.h)*
* Return: return the final result of the string in char
*/
char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}

	for (j = 0; src[j] != '\0'; j++, i++)
	{
		dest[i] = src[j];
	}


	return (dest);
}
/**
 * _strlen - this functions prints the lenght of a string
 * @s: string to print.
 * Description: this function prints the lenght of a string
 * section header: the header of this function is hsh.h
 * Return: retunrn the lenght in int
 **/
int _strlen(char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;
	return (len);
}
/**
 * _strdup - this functions copy a string.
 * @str: the string to copy
 * Description: this function copy a string)?
 * section header: the header of this function is hsh.
 * Return: this is a void function no return
 **/
char *_strdup(char *str)
{
	char *p;
	int i, s;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
		i++;
	p = malloc(i * sizeof(*str) + 1);
	if (p == NULL)
		return (NULL);
	for (s = 0; s < i; s++)
		*(p + s) = *(str + s);
	*(p + s) = '\0';
	return (p);
}
/**
 * _strcmp - this function compare two strings
 * @s1: the first string
 * @s2: the second string
 (* a blank line
 * Description: this function comparing two strings using the first value)?
(* section header: the header of this function is holberton.h)*
* Return: return a number depends os the resul fo comparation.
*/
int _strcmp(char *s1, char *s2)
{
	int j;

	for (j = 0; s1[j] != '\0' || s2[j] != '\0'; j++)
	{
		if (s1[j] != s2[j])
		{
			return (s1[j] - s2[j]);
		}
	}
	return (0);
}
/**
 * _strstr - this function compare two strings
 * @haystack: the string to search
 * @needle: tthe string where gonna search
 * a blank line
 * Description: this function comparing two strings using the first value)?
 * section header: the header of this function is holberton.h)*
 * Return: return a number depends os the resul fo comparation.
 */
char *_strstr(char *haystack, char *needle)
{

	while (*haystack != '\0')
	{
		char *i = haystack;
		char *j = needle;

		while (*j == *haystack && *j != '\0' && *haystack != '\0')
		{
			haystack++;
			j++;
		}
		if (*j == '\0')
			return (i);
		haystack = i + 1;
	}
	return (NULL);
}
