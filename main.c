#include "main.h"
/**
 * main - Minimal shell for Task 0.1
 *
 * Return: 0 on success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	char *argv[2];
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			printf("#cisfun$ ");

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}
		line[strcspn(line, "\n")] = '\0';

		pid = fork();
		if (pid == 0)
		{
			argv[0] = line;
			argv[1] = NULL;
			execve(argv[0], argv, environ);
			perror("./shell");
			exit(1);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		else
		{
			perror("fork");
		}
	}
	free(line);
	return (0);
}
