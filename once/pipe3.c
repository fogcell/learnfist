#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int data_processed;
	int file_pipes[2];
	const char somg_data[] = "CUDA";
	char buffer[BUFSIZ + 1];
	pid_t fork_result;

	memset(buffer, '\0',sizeof(buffer));

	if (pipe(file_pipes) == 0){
		fork_result = fork();
		if (fork_result == (pid_t)-1){
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}//success
		if (fork_result == 0){//in chile process 
			sprintf(buffer, "%d", file_pipes[0]);
			(void)execl("pipe4", "pipe4", buffer, (char *)0);
			exit(EXIT_FAILURE);
		}
		else {//in parent process
			data_processed = write(file_pipes[1], somg_data,
											strlen(somg_data));
			printf("%d - wrote %d bytes\n",getpid(), data_processed);
		}
	}
	exit(EXIT_SUCCESS);
}
