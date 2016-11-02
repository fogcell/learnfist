#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char *argv[])
{
	int data_processed;
	char buffer[BUFSIZ + 1];
	int file_descripetor;

	memset(buffer, '\0', sizeof(buffer));
	sscanf(argv[1], "%d", &file_descripetor);
	data_processed = read(file_descripetor, buffer, BUFSIZ);

	printf("%d - read %d bytes: %s\n",getpid(), data_processed, buffer);
	exit(EXIT_SUCCESS);
}
