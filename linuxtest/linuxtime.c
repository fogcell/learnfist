#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main() {
    struct timeval start;
    struct tm *local_time = NULL;
    static char str_time[100];
    char ms[16];
    gettimeofday( &start, NULL );
    local_time = localtime(&start.tv_sec);
    strftime(str_time, sizeof(str_time), "%Y-%m-%dT%H:%M:%S", local_time);
    sprintf(ms,".%ld",start.tv_usec);
    strcat(str_time,ms);
    printf("time: %s \n", str_time);
    return 0;
}
