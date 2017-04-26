#define DOWNLOAD_DIAG_FILE "/tmp/downloadfile"
#define DOWNLOAD_WGET_LOG "/tmp/wget.log"
#define MAX_DOWNLOADFILE_SIZE 10*1024*1024
struct timeval BOMTime;
struct timeval EOMTime;
int read_memory(char *shellcmd, char *out, int size) {

  FILE *stream;
  char buffer[size];
  memset(buffer, 0, sizeof(buffer));

  stream = popen(shellcmd, "r");
  if (stream != NULL) {
    fread(buffer, sizeof(char), sizeof(buffer), stream);
    pclose(stream);
    memcpy(out, buffer, strlen(buffer) + 1);
    return 0;
  } else {
    out[0] = '\0';
  }
  return -1;
}
int check_ftp_receive_state(const char *fromurl, const char * tofile, const char * pUsername, const char * pPassword)
{
  char shellcmd[256] = {0};
  char buffer[512] = {0};
  int size_of_file = 0;
    
  if (pUsername == NULL||strlen(pUsername) == 0) {
    sprintf(shellcmd,"wget --timeout=5 --tries=1 -o %s --spider %s ", DOWNLOAD_WGET_LOG, fromurl);
    //--spider Test download the file, this time has not yet downloaded
    // --timeout=2 Set the timeout time 5s  --tries=1 Set the number of retries If specified as 0, it means an unlimited number of retries
  } else { //This branch is not used
    sprintf(shellcmd, "wget --timeout=5 --tries=1 -o %s --spider ftp://%s:%s@%s",
            DOWNLOAD_WGET_LOG,
            pUsername,
            pPassword,
            fromurl+6);
  }
    system(shellcmd);
    memset(shellcmd,0,sizeof(shellcmd));
    sprintf(shellcmd,"cat  %s | grep \"==> SIZE\" | awk \'{print $5}\'", DOWNLOAD_WGET_LOG);
    read_memory(shellcmd,buffer,sizeof(buffer));
    if(strlen(buffer) != 0) {
        size_of_file = atoi(buffer);
        memset(shellcmd,0,sizeof(shellcmd));
        memset(buffer,0,sizeof(buffer));
        sprintf(shellcmd,"cat %s | grep \"No such file\"", DOWNLOAD_WGET_LOG);//NO such file
        read_memory(shellcmd,buffer,sizeof(buffer));
        if(strlen(buffer) != 0) {
          error("Error_TransferFailed");//no such file
          return -1;
         } else {
              if (size_of_file > MAX_DOWNLOADFILE_SIZE) {//10*1024*1024
                  debug("[ftp_receive_file] file_Size > 10M");
                  error("Error_IncorrectSize");
                  return -1;
               }
          }
    } else {
        memset(shellcmd,0,sizeof(shellcmd));
        memset(buffer,0,sizeof(buffer));
        sprintf(shellcmd,"cat %s | grep \"failed: Connection timed out\"", DOWNLOAD_WGET_LOG);//timed out
        read_memory(shellcmd,buffer,sizeof(buffer));
        if(strlen(buffer) != 0) {
            set_download_state("Error_Timeout");
            return -1;
         } else {
          memset(shellcmd,0,sizeof(shellcmd));
            memset(buffer,0,sizeof(buffer));
            sprintf(shellcmd,"cat %s | grep \"Error in server response\"", DOWNLOAD_WGET_LOG);//no response
            read_memory(shellcmd,buffer,sizeof(buffer));
            if(strlen(buffer) != 0) {
                error("Error_NoResponse");
                return -1;
            } else {
              memset(shellcmd,0,sizeof(shellcmd));
              memset(buffer,0,sizeof(buffer));
              sprintf(shellcmd,"cat %s | grep \"Login incorrect\"", DOWNLOAD_WGET_LOG);//Login faild
              read_memory(shellcmd,buffer,sizeof(buffer));
              if(strlen(buffer) != 0) {
                  error("Error_LoginFailed");
                  return -1;
              } else {
                  error("Error_InitConnectionFailed");
                  return -1;
              }
            }
         }
    }
  return 0;
}
int ftp_receive_file(const char *fromurl, const char * tofile, const char * pUsername, const char * pPassword)
{
  char buff[512] = {0};
  int ret = 0;
  ret = check_ftp_receive_state(fromurl,tofile,pUsername,pPassword);
  if (remove(DOWNLOAD_WGET_LOG) != 0) {
    error("[ftp_receive_file]:%s remove failed", DOWNLOAD_WGET_LOG);
  }
  if (ret != 0) {
    return -1;
  }
  gettimeofday(TCPOpenRequestTime,NULL);
  if (pUsername == NULL||strlen(pUsername) == 0) {
    sprintf(buff, "wget --timeout=5 --tries=1 -o %s %s -O %s", DOWNLOAD_WGET_LOG, fromurl, tofile);//-o Output log to file
    // --timeout=2 Set the timeout time 5s  --tries=1 Set the number of retries If specified as 0, it means an unlimited number of retries
  } else {
    sprintf(buff, "wget --timeout=5 --tries=1 -o %s ftp://%s:%s@%s -O %s",
            DOWNLOAD_WGET_LOG,
            pUsername,
            pPassword,
            fromurl+6,
            tofile);
  }
  debug("[ftp_receive_file] download.sh:\n%s", buff);
  gettimeofday(&BOMTime,NULL);
  system(buff);
  gettimeofday(&EOMTime,NULL);
  //read_memory("cat /tmp/tr069_wget.log | grep Length: | awk \'{print $2}\'",buff,sizeof(buff));

  if (remove(DOWNLOAD_WGET_LOG) != 0) {
    error("[ftp_receive_file]:%s remove failed", DOWNLOAD_WGET_LOG);
  }
  return 0;

}
