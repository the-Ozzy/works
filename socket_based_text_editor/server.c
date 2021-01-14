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
    socket_descriptor = socket(AF_INET,SOCK_STREAM,0);

    if (socket_descriptor < 0)
        return EXIT_FAILURE;
    puts("soket acildi");

    struct sockaddr_in server_addr, cli_addr;
    server_addr.sin_port = htons(2077);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(socket_descriptor,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
        return EXIT_FAILURE;
    puts("bindlendi");
    if(listen(socket_descriptor,4) < 0)
        return EXIT_FAILURE;
    puts("listenlendi");
    
    int fd = open("test.txt",O_CREAT,O_RDWR,O_APPEND);
    if (fd < 0)
        return EXIT_FAILURE;
    puts("dosya acildi");
    socklen_t cli_socken = sizeof(cli_addr);
    char cli_m[1024];
    char ser_m_accept[] = "yazildi\n";
    char ser_m[] = "Yaziliyor...\n";
    cli_sock_desc = accept(socket_descriptor,(struct sockaddr*)&cli_addr,&cli_socken);
    if (cli_sock_desc < 0)
        return EXIT_FAILURE;
    //fwrite(fd,"Hellothrere\n",sizeof("Hellothrere\n"));
    while(true){
        memset(cli_m, '\0',sizeof(cli_m));
        if (recv(cli_sock_desc, cli_m, sizeof(cli_m) ,0) < 0)
            return EXIT_FAILURE;
        if (strcmp(cli_m,"END") == 0){puts("END");
            return EXIT_SUCCESS;}
        if (send(cli_sock_desc,ser_m,strlen(ser_m), 0) < 0)
            return EXIT_FAILURE;
        if(write(fd,cli_m,strlen(cli_m))<0){ /// ***********************
            puts("dosya hatasi");
        }
        printf("%s\n",cli_m);
        if (send(cli_sock_desc,ser_m_accept,strlen(ser_m_accept), 0) < 0)
            return EXIT_FAILURE;
    }
    if(close (cli_sock_desc)< 0)
        return EXIT_FAILURE;
    if(close(fd) < 0)
        return EXIT_FAILURE;
    if(close(socket_descriptor) < 0)
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}
