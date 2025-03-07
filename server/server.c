#include <stdio.h>     // printf, perror
#include <stdlib.h>    // exit()
#include <string.h>    // strlen()
#include <unistd.h>    // close()
#include <arpa/inet.h> // socket(), bind(), listen(), accept(), etc.

#define PORT 25518 // The port nuymber the server will listen on
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, client_fd;       // Initialize server and client file descriptors
    struct sockaddr_in server_addr; // Initialize server address structure
    char buffer[BUFFER_SIZE] = {0};

    // Create a socketn (IPv4, TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind Socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 1);

    printf("Server listening on port %d\n", PORT);

    // Accept Connection
    client_fd = accept(server_fd, (struct sockaddr *)NULL, NULL);
    if (client_fd < 0)
    {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Client connected\n");

    // Send File
    FILE *file = fopen("server_file.png", "r");
    int bytes;
    while ((bytes = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        send(client_fd, buffer, bytes, 0);
    }
    printf("File sent successfully\n");
    fclose(file);

    // Close the connection
    close(client_fd);
    close(server_fd);

    return 0;
}