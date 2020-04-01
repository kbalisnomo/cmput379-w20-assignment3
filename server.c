/* CMPUT379 W20 Assignment 3 Submission.
   This is the server portion of the client-server problem.
   Name: Kyle Philip Balisnomo
   CCID: kylephil                                       */

#include "server.h"

int main(int argc, char *argv[]) {
   int port = atoi(argv[1]);
   int listenfd = 0, connfd = 0, transactions = 0, n, len;
   struct sockaddr_in serv_addr; 
   char sendBuff[1025];
   char recvBuff[1024];
   char *command;
   char *machine;
   struct timeval tv = {60, 0};
   
   listenfd = socket(AF_INET, SOCK_STREAM, 0);
   memset(&serv_addr, '0', sizeof(serv_addr));
   memset(sendBuff, '0', sizeof(sendBuff)); 

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   serv_addr.sin_port = htons(port);
   printf("Using port %d\n", port); 

   bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

   listen(listenfd, 10); 

   while(1)
   {
      // if (select(0, NULL, NULL, NULL, &tv) > 0) {
      //    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
      //    read(connfd, recvBuff, 1024); //receive a string in the form "Tn machine.pid"
      //    transactions++;
      //    command = strtok(recvBuff, " ");
      //    machine = strtok(NULL, " ");
      //    memmove(command, command+1, strlen(command));
      //    n = atoi(command);
      //    printf("%.2f: # %2d (T%3d) from %s\n", (float)time(NULL), transactions, n, machine);
      //    Trans(n);
      //    printf("%.2f: # %2d (Done) from %s\n", (float)time(NULL), transactions, machine);
      //    snprintf(sendBuff, 1025, "%d", transactions);
      //    send(connfd, sendBuff, strlen(sendBuff), 0);
      //    close(connfd);
      //    sleep(1);
      // }
      // else {
      //    break;
      // }
      connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
      read(connfd, recvBuff, 1024); //receive a string in the form "Tn machine.pid"
      transactions++;
      command = strtok(recvBuff, " ");
      machine = strtok(NULL, " ");
      memmove(command, command+1, strlen(command));
      n = atoi(command);
      printf("%.2f: # %2d (T%3d) from %s\n", (float)time(NULL), transactions, n, machine);
      Trans(n);
      printf("%.2f: # %2d (Done) from %s\n", (float)time(NULL), transactions, machine);
      snprintf(sendBuff, 1025, "%d", transactions);
      send(connfd, sendBuff, strlen(sendBuff), 0);
      close(connfd);
      sleep(1);
   }
   printf("\nSUMMARY");
   printf("");
}