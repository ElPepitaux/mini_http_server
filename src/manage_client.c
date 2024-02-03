/*
** EPITECH PROJECT, 2024
** mini_http_server
** File description:
** manage_client
*/

#include "server.h"

void *create_client(va_list *ap)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        return NULL;
    client->socket = va_arg(*ap, int);
    client->addr = va_arg(*ap, struct sockaddr_in);
    return client;
}

void destroy_client(void *data)
{
    client_t *client = (client_t *)data;

    close(client->socket);
    free(client);
}
