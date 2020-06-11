#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr;  
    char buffer[1024] = {0};
    char ipAddress[16]; 
    char *filePath;
    FILE *fp; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    
   printf("%s\n", "enter an IP address to connect to.");
   scanf("%s", &ipAddress[0]);

    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, ipAddress, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer );

    printf("%s\n", "please enter a file path to send");
    scanf("%s", filePath);
    
    fp = fopen(filePath, "rb");
    if(fp == NULL){printf("%s\n", "error opening file for reading"); return 1;}
 

    fseek(fp, 0, SEEK_END);
    long file_Size=ftell(fp); 

    if(file_Size > 0){ 
    fseek(fp, 0, SEEK_SET);
    


    while(ftell(fp) < file_Size){
    memset(buffer, '\0', 1024);
    fread(buffer, 1024, 1, fp);
    printf("%ld\n", ftell(fp));
    send(sock, buffer, 1024, 0);
    }
    }
    fclose(fp);
    
    return 0; 
} 
