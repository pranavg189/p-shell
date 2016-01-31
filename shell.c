void shell_loop(void);
char *shell_read_line(void);

int main(int argc, char **argv)
{
	// Load Config files - to be added in future

	// Run command loop
	shell_loop();

	// Perform any shutdown/cleanup

	return EXIT_SUCCESS;
}

void shell_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("> ")
		line = shell_read_line();
		args = shell_split_line(line);
		status = shell_execute(args);

		free(line);
		free(args);
	} while(status);
}

#define SHELL_RL_BUFSIZE 1024
char *shell_read_line(void)
{
	int bufsize = SHELL_RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);

	if(!buffer) {
		fprintf(stderr, "psh:allocation error\n");
		exit(EXIT_FAILURE);

	}
}

