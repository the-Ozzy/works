#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define true 1
#define false 0

int main (void){
    int socket_descriptor, cli_sock_desc;
    // opening the socket
    socket_descriptor = socket(AF_INET,SOCK_STREAM,0);
    // checking about socket() function's state
    if (socket_descriptor < 0)
        return EXIT_FAILURE;
    puts("Opening the socket is success");
    
    // creating server's and child's id in server
    struct sockaddr_in server_addr, cli_addr;
    server_addr.sin_port = htons(2077);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    char client_message[1024], server_message[1024];
    // connecting to server
    if (connect(socket_descriptor,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
        return EXIT_FAILURE;
    while (true){
    memset(client_message, '\0',sizeof(client_message));
    memset(server_message, '\0',sizeof(server_message));
    // taking string from user
    printf("Write your sentences and press ENTER\n\n->");
    fgets(client_message,1024,stdin);
    strtok(client_message,"\n");
    // checking for END keyword so that program cuts before other connections
    if(strcmp(client_message,"END") == 0){
        if (send(socket_descriptor,client_message,strlen(client_message),0) < 0)
            return EXIT_FAILURE;
        return EXIT_SUCCESS;
    }
     // sending string to server
    if (send(socket_descriptor,client_message,strlen(client_message),0) < 0)
        return EXIT_FAILURE;
     //getting string from server
    if (recv(socket_descriptor,server_message,strlen(server_message),0) < 0)
        return EXIT_FAILURE;
    
    printf("SERVER: %s\n",server_message);
    }
    return EXIT_SUCCESS;
}
