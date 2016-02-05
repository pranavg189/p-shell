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

/* Function to read a line */
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

	while(1){
		// Read a character
		c = getchar();

		// If we hit EOF, replace it with a null character and return.
		if(c == EOF || c == '\n') {
			buffer[position] = '\0';
			return buffer;
		} else {
			buffer[position]=c;
		}
		position++;

		// If we have exceeded buffer, reallocate

		if(position >= bufsize) {
			bufsize += LSH_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if(!buffer) {
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/* Function to parse a given line */
#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \t\r\n\a"
char **shell_split_line(char *line)
{
	int bufsize = SHELL_TOK_BUFSIZE, position=0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if(!tokens) {
		fprintf(stderr, "shell: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, SHELL_TOK_DELIM);
	while(token != NULL) {
		tokens[position] = token;
		position++;

		/* if buffer exceeded, reallocate the buffer */
		if(position >= bufsize) {
			bufsize += SHELL_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if(!tokens) {
				fprintf(stderr, "shell: allocation error \n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, SHELL_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}



