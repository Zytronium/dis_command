#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int charEquals(int c, ...);
void removeChars(char *str, char *charsToRemove);

/**
 * main - entry point
 * @argc: Number arguments supplied to the command, including program name
 * @argv: Arguments supplied to the command, including program name
 * Return: always 0
 */
int main(int argc, char **argv)
{
	char *flags, *places, *cmd;
	int i = 1, j, echo = 0, numPlaces = 0;

	if (argc == 1)
	{
		printf("Contents of the current directory:\n");
		system("ls --color=auto");
	}
	else
	{
		/* Allocate enough memory for cmd to hold the longest possible command */
		cmd = malloc(sizeof(char) * 1024);
		if (cmd == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			exit(EXIT_FAILURE);
		}
		strcpy(cmd, "ls --color=auto");

		/* Allocate enough memory for flags to hold all arguments */
		flags = malloc(sizeof(char) * argc * 2);
		if (flags == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			free(cmd);
			return EXIT_FAILURE;
		}
		flags[0] = '\0';

		/* Allocate memory for places */
		places = malloc(sizeof(char) * 1024);
		if (places == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			free(cmd);
			free(flags);
			return EXIT_FAILURE;
		}
		places[0] = '\0';

		while (i < argc)
		{ /* iterate through args */
			char *arg = argv[i];
			j = 1; /* reset j for each argument */

			if (arg[0] == '-')
			{ /* iterate through chars in arg */
				while (arg[j] != '\0')
				{
					if (arg[j] == 'e') /* checks for custom flag -e */
						echo = 1; /* -e surrounds cmd output in empty lines */
					else if (arg[j] == 'E') /* checks for custom flag -E */
						echo = -1; /* -E prevents empty line between ls & pwd */
					else if (!charEquals(arg[j], 'l', 'a', 'A', 'b', 'B', 'c',
										   'C', 'd', 'D', 'f', 'F', 'g', 'G',
										   'h', 'H', 'i', 'I', 'k', 'L', 'm',
										   'n', 'N', 'o', 'p', 'q', 'Q', 'r',
										   'R', 's', 'S', 't', 'T', 'u', 'U',
										   'v', 'w', 'x', 'X', 'Z', '1', '\0'))
					{ /* ^checks if the current char is a valid flag for ls^ */
						fprintf(stderr, "dis: invalid option -- '%c'\n"
										"Flags for dis are identical to "
										"single-letter flags for ls\n"
										"Try 'ls --help' for more info.\n",
								arg[j]);
						free(cmd);
						free(flags);
						free(places);
						exit(EXIT_FAILURE);
					}
					j++;
				}
				strcat(flags,&arg[1]); /* appends the flag chars in this string to the flags string, starting after the '-' char */
			}
			else
			{
				strcat(places, arg);
				strcat(places, " ");
				numPlaces++;
			}
			i++;
		}

		removeChars(flags, "eE"); /* Remove 'e' and 'E' from flags */

		if (strlen(flags) > 0)
		{
			strcat(cmd, " -"); /* 'ls -' */
			strcat(cmd, flags); /* 'ls -flags' */
		}

		if (strlen(places) > 0)
		{
			strcat(cmd, " "); /* ensure a space before places */
			strcat(cmd, places); /* 'ls -flags places ' */
		}

		if (echo == 1) /* -e | surrounds cmd output in empty lines */
			putchar('\n');
		if (numPlaces == 0)
			printf("Contents of the current directory:\n");
		else if (numPlaces == 1)
			printf("Contents of the given directory:\n");
		else
			printf("Contents of the given directories:\n");

		system(cmd);
		free(cmd);
		free(flags);
		free(places);
	}

	if (echo != -1) /* -E | prevents empty line between ls & pwd output */
		putchar('\n');
	printf("Current directory:\n");
	system("pwd");
	if (echo == 1) /* -e | surrounds cmd output in empty lines */
		putchar('\n');

	return (EXIT_SUCCESS);
}

/**
 * charEquals - checks if the first given character is any of the other given characters.
 * @c: char to check if it equals any of the others
 * @...: other chars to check if c is equal to
 * Return: 1 if any of the given chars are equal to the first, otherwise, 0.
 */
int charEquals(int c, ...)
{
	va_list args;
	char check;

	va_start(args, c);
	check = va_arg(args, int);
	while (check != '\0')
	{
		if ((char) c == check)
		{
			va_end(args);
			return (1);
		}
		check = va_arg(args, int);
	}
	va_end(args);

	return (0);
}
/**
 * removeChars - removes all occurrences of the characters in charsToRemove from str
 * 100% AI Generated function
 * @str: the string to remove characters from
 * @charsToRemove: the characters to remove from str
 */
void removeChars(char *str, char *charsToRemove)
{
	int src, dst = 0;
	char *remove;

	for (src = 0; str[src] != '\0'; src++)
	{
		for (remove = charsToRemove; *remove != '\0'; remove++)
		{
			if (str[src] == *remove)
				break;
		}
		if (*remove == '\0') { /* if character not found in charsToRemove */
			str[dst++] = str[src];
		}
	}
	str[dst] = '\0'; /* null terminate the result */
}
