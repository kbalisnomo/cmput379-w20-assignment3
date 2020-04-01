/* CMPUT379 W20 Assignment 3 Submission.
   This is the client portion of the client-server problem.
   Name: Kyle Philip Balisnomo
   CCID: kylephil                                       */

#include "client.h"
#include <errno.h>

int main(int argc, char *argv[]) {
    struct sockaddr_in serv_addr; 
    char recvBuff[1024];
    int sock_fd = 0, n = 0, transactions = 0;
    int port = atoi(argv[1]);
    char *ip_addr = argv[2];
    char command[3];
    FILE *file;
    char filename[256];
    char host_buff[128];
    char pid_buff[128];
    pid_t pid;
    char sendBuff[1025];

    gethostname(host_buff, sizeof(host_buff)); 
    pid = getpid();
    snprintf(pid_buff, 128, "%d", pid);
    strcpy(filename, host_buff);
    strcat(filename, ".");
    strcat(filename, pid_buff);
    strcat(filename, ".log");
    file = fopen(filename, "w");
    fprintf(file, "Using port %d\n", port);
    fprintf(file, "Using server address %s\n", ip_addr);
    fprintf(file, "Host %s\n", filename);
    printf("%s.%d\n", host_buff, pid);

    if(argc != 3) {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 

    while(scanf("%s", command) == 1) {
        if (command[0] == 'T') {
            if((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                printf("\n Error : Could not create socket \n");
                return 1;
            } 

            memset(&serv_addr, '0', sizeof(serv_addr)); 

            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(port); 

            if(inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr)<=0)
            {
                printf("\n inet_pton error occured\n");
                return 1;
            } 

            if(connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
                printf("\n Error : Connect Failed \n");
                perror("This error occurred");
                return 1;
            }
            strcpy(sendBuff, command);
            strcat(sendBuff, " ");
            strcat(sendBuff, filename);
            send(sock_fd, sendBuff, strlen(sendBuff), 0);
            memmove(command, command+1, strlen(command));
            fprintf(file, "%.2f: Send (T%s)\n", (float)time(NULL), command);
            transactions++;
            read(sock_fd, recvBuff, sizeof(recvBuff)-1);
            fprintf(file, "%.2f: Recv (D%s)\n", (float)time(NULL), recvBuff);
        }
        else if (command[0] == 'S') {
            Sleep(command[1]);
            memmove(command, command+1, strlen(command));
            fprintf(file, "Sleep %s units\n", command);
        }
    }

    fprintf(file, "Sent %d transactions", transactions);
    fclose(file);
    return 0;

}