/*
** EPITECH PROJECT, 2024
** mini_http_server
** File description:
** server
*/

#include "server.h"

bool create_connection(server_t *server)
{
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1) {
        perror("FAILED TO CREATE SOCKET\n");
        exit(84);
    }
    server->addr.sin_family = AF_INET;
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->addr.sin_port = htons(server->port);
    int opt = 1;
    int peer_adress_len = sizeof(server->addr);
    if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) < 0) {
        perror("SETSOCKET FAILED\n");
        exit(84);
    }
    if (bind(server->socket, (struct sockaddr*)&server->addr, sizeof(server->addr)) < 0) {
        perror("FAILED TO BIND\n");
        exit(84);
    }
    printf("Listening on port %d.\n", server->port);
    if (listen(server->socket, SOMAXCONN) == -1) {
        perror("FAILED TO LISTEN\n");
        exit(84);
    }
    client_t *newClient = malloc(sizeof(client_t));
    if ((newClient->socket = accept(server->socket, (struct sockaddr*)&newClient->addr, (socklen_t *)&peer_adress_len)) < 0) {
        free(newClient);
        perror("CONNECTION FAILED\n");
        exit(84);
    }
    printf("Client connected ! IP: %s Port: %d\n", inet_ntoa(newClient->addr.sin_addr), ntohs(newClient->addr.sin_port));
    server->clients = newClient;
    return 0;
}

void destroy_server(server_t *server)
{
    close(server->socket);
    free(server->clients);
}
