/*
** EPITECH PROJECT, 2024
** mini_http_server
** File description:
** server
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct client_s {
    int socket;
    struct sockaddr_in addr;
} client_t;

typedef struct server_s {
    struct sockaddr_in addr;
    int socket;
    int port;
    client_t *clients;
} server_t;

void sendHeader(server_t *server, const char *content, const char *type);
void getFile(server_t *server, char *buffer);
bool create_connection(server_t *server);
void destroy_server(server_t *server);

#endif /* !SERVER_H_ */
