#include "timeit.h"


pid_t	pid;
time_t	start;
time_t	end;
int	status;

void	error(char *str)
{
	printf("%s\n", str);
	exit(0);
}

void	check_params(char **argv, int *time_allowed, char **path)
{
	*time_allowed = atoi(argv[1]);
	if (*time_allowed < 0)
		error("Execution time must be a positive number.");
	if (*time_allowed == 0)
		printf("Execution time is set to 0. Is everything right?\n");
	*path = strdup(argv[2]);
	if (!(*path))
		error("Path is undefined.");
}

void	child_kill()
{
	if (kill(pid, SIGKILL))
		error("Killing of the child process failed.");
	waitpid(pid, &status, 0);	//	Release the resources associated with child process
	printf("\nChild process was killed because of the time limit.\n");
	exit(0);
}

void	child_end()
{
	if (WIFEXITED(status) == 0)	//	Process was killed
		return;

	end = time(0);
	printf("\nChild process execution time: %d s\n", (int)(end - start));
}

int main(int argc, char **argv)
{
	int	time_allowed;
	char	*path;

	if (argc < 3)
		error("Usage: ./timeit [time_allowed] [app_path] [app_arguments]");

		//	Defining parameters
	check_params(argv, &time_allowed, &path);	//	Check if parameters are valid
	signal(SIGALRM, child_kill);
	signal(SIGCHLD, child_end);
	start = time(0);

		//	Creating a new process using fork()
	pid = fork();
	if (pid < 0)
		error("Couldn't create child process.");

	if (pid == 0)	//	Child process
	{
		if (execv(path, &argv[2]) == -1)	//	Launching the application with some arguments
			error("Error has occured while executing child process.");
	}
	else	//	Parent process
	{
		alarm(time_allowed);
		waitpid(pid, &status, 0);
	}
	free(path);
	return (0);
}
