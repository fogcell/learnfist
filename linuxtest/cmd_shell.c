int cmd_shell(char *shellcmd, char *outbuffer, int size) {

    FILE *stream;
    char buffer[size];
        memset(buffer, 0, sizeof(buffer));

    stream = popen(shellcmd, "r");
    if (stream != NULL) {
            fread(buffer, sizeof(char), sizeof(buffer), stream);
            pclose(stream);
            memcpy(outbuffer, buffer, strlen(buffer) + 1);

            return 0;
    } else {
        outbuffer[0] = '\0';
    }
    return -1;
}  
//ifconfig eth0 | grep "RX bytes" | awk '{print $2}' | sed 's/bytes://g'
//ifconfig eth0 | grep "RX bytes" | awk '{print $2}' | awk -F: '{print $2}'
