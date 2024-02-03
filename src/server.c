/*
** EPITECH PROJECT, 2024
** mini_http_server
** File description:
** server
*/

#include "server.h"

server_t *create_server(int port)
{
    server_t *server = malloc(sizeof(server_t));
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server == NULL)
        return NULL;
    if (server->socket == -1) {
        perror("FAILED TO CREATE SOCKET\n");
        return NULL;
    }
    server->port = port;
    server->addr.sin_family = AF_INET;
    server->addr.sin_addr.s_addr = INADDR_ANY;
    server->addr.sin_port = htons(server->port);
    int opt = 1;
    if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt)) < 0) {
            perror("SETSOCKET FAILED\n");
            return NULL;
        }
    if (bind(server->socket, (struct sockaddr*)&server->addr, sizeof(server->addr)) < 0) {
        perror("FAILED TO BIND\n");
        return NULL;
    }
    printf("Listening on port %d.\n", server->port);
    server->clients = create_list(create_client, destroy_client);
    return server;
}

void *create_connection(server_t *server)
{
    int socketclient = 0;
    struct sockaddr_in addr;
    int peer_adress_len = sizeof(server->addr);
    if (listen(server->socket, SOMAXCONN) == -1) {
        perror("FAILED TO LISTEN\n");
        return NULL;
    }
    if ((socketclient = accept(server->socket, (struct sockaddr*)&addr, (socklen_t *)&peer_adress_len)) < 0) {
        perror("CONNECTION FAILED\n");
        return create_connection(server);
    }
    printf("Client connected ! IP: %s Port: %d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    push_back_list(server->clients, socketclient, addr);
    return NULL;
}

void destroy_server(server_t *server)
{
    close(server->socket);
    destroy_list(&server->clients);
    free(server);
}
