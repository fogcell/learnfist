int read_meminfo(char *mem_total, char *mem_free)
{
    FILE *file_handle;
    const char * meminfo_file ="/proc/meminfo";
    char buffer[128];
    int len = 0;
    char *p1;
    file_handle = fopen(meminfo_file,"r");
    if (file_handle == NULL) {
        return -1;
    }

    while ( fgets(buffer,sizeof(buffer) - 1, file_handle) != NULL) {
        p1 = strchr(buffer, ':');
        if (! strncmp(buffer,"MemTotal", p1 - buffer)) {

            sscanf(p1+1,"%s%*s",mem_total);
            len = strlen(mem_total);
            *(mem_total+len) = ' ';
            sscanf(p1+1,"%*s%s",mem_total+len+1);

        } else if (! strncmp(buffer,"MemFree", p1 - buffer)) {

            sscanf(p1,"%*s%s",mem_free);
            len = strlen(mem_free);
            *(mem_free+len) = ' ';
            sscanf(p1+1,"%*s%s",mem_free+len+1);
            break;
        }
    }
    fclose(file_handle);
    return 0;
}
