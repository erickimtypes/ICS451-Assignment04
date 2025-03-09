/**
 * NAME        : Eric Kim
 *
 * HOMEWORK    : 04
 *
 * CLASS       : ICS 451
 *
 * INSTRUCTOR  : Ravi Narayan
 *
 * DATE        : 03/08/2025
 *
 * FILE        : client.c
 *
 * DESCRIPTION : This file contains the client-side implementation for a file transfer program in Homework 04.
 *               It establishes a TCP connection to the server, receives a file in chunks, and saves it as "client_file.png"
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 25518
#define BUFFER_SIZE 1024

/**
 * The main method to start the client.
 *
 * @param args Command line arguments. Does not expect any arguments
 */
int main()
{
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Create Socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Connect to Server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server!\n");

    // Receive File
    FILE *file = fopen("client_file.png", "w");
    int bytes;
    while ((bytes = recv(client_fd, buffer, BUFFER_SIZE, 0)) > 0)
    {
        fwrite(buffer, 1, bytes, file);
    }
    printf("File received successfully.\n");
    fclose(file);

    // Close Connection
    close(client_fd);
    return 0;
}
