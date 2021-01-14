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
    
    // binding the socket to program
    if(bind(socket_descriptor,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
        return EXIT_FAILURE;
    puts("Binding is complete");
    
    //listening
    if(listen(socket_descriptor,4) < 0)
        return EXIT_FAILURE;
    puts("Listening...");
    
    int fd = open("test.txt",O_CREAT,O_RDWR,O_APPEND);// creating or opening the text file which program will write later on
    if (fd < 0)
        return EXIT_FAILURE;
    puts("File opened Succesfully");
    
    socklen_t cli_socken = sizeof(cli_addr);
    char cli_m[1024];
    char ser_m_accept[] = "Written\n";
    char ser_m[] = "Writing...\n";
    // accepting server request, doing this out of while repetition because server is focused on one continous client for now
    cli_sock_desc = accept(socket_descriptor,(struct sockaddr*)&cli_addr,&cli_socken);
    if (cli_sock_desc < 0)
        return EXIT_FAILURE;
    while(true){
        memset(cli_m, '\0',sizeof(cli_m));
        //recieving data from client
        if (recv(cli_sock_desc, cli_m, sizeof(cli_m) ,0) < 0)
            return EXIT_FAILURE;
        // looking for END keyword to end process 
        if (strcmp(cli_m,"END") == 0){puts("END");
            return EXIT_SUCCESS;}
        // sending message to client
        if (send(cli_sock_desc,ser_m,strlen(ser_m), 0) < 0)
            return EXIT_FAILURE;
        //writing to file, but for now its broken somehow
        if(write(fd,cli_m,strlen(cli_m))<0){ /// ***********************
            puts("File Error");
        }
        printf("%s\n",cli_m);
        // sending written info to client
        if (send(cli_sock_desc,ser_m_accept,strlen(ser_m_accept), 0) < 0)
            return EXIT_FAILURE;
    }
    // closing sockets and file
    if(close (cli_sock_desc)< 0)
        return EXIT_FAILURE;
    if(close(fd) < 0)
        return EXIT_FAILURE;
    if(close(socket_descriptor) < 0)
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}
