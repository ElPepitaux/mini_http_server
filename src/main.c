/*
** EPITECH PROJECT, 2024
** mini_http_server
** File description:
** main
*/

#include "server.h"

void My_strlen_server(client_t *client, char *buffer)
{
    char *str = NULL;
    int len = 0;
    printf("Data received: \"%s\"\n", buffer);
    len = snprintf(str, 0, "The length of \"%s\" is %d", buffer, (int)strlen(buffer));
    str = malloc(sizeof(char) * (len + 1));
    sprintf(str, "The length of \"%s\" is %d", buffer, (int)strlen(buffer));
    sendHeader(client, str, "application/octet-stream");
    free(str);
}

bool manage_request(client_t *client)
{
    char buffer[1024] = {0};
    char *request = NULL;
    char cpy[1024] = {0};
    if (read(client->socket, buffer, 1024) <= 0)
            return false;
    strcpy(cpy, buffer);
    request = strtok(cpy, " ");
    if (strcmp(request, "GET") == 0 || strcmp(request, "HEAD") == 0)
        getMethode(client, buffer);
    else
        My_strlen_server(client, buffer);
    return true;
}

void process(server_t *server)
{
    fd_set readfds;
    while (true) {
        FD_ZERO(&readfds);
        FD_SET(server->socket, &readfds);
        for (linked_list_t *tmp = server->clients->nodes; tmp; tmp = tmp->next)
            FD_SET(CAST(client_t *, tmp->data)->socket, &readfds);
        if (select(FD_SETSIZE, &readfds, NULL, NULL, NULL) < 0)
            return;
        if (FD_ISSET(server->socket, &readfds)) {
            create_connection(server);
            continue;
        }
        for (linked_list_t *tmp = server->clients->nodes; tmp; tmp = tmp->next) {
            client_t *client = CAST(client_t *, tmp->data);
            if (FD_ISSET(client->socket, &readfds)) {
                if (!manage_request(client)) {
                    printf("Client disconnected\n");
                    remove_node(&server->clients, tmp, destroy_client);
                    break;
                }
            }
        }
    }
}

int main(int ac, char **av)
{
    server_t *server = NULL;
    int port = 0;
    if (ac != 2)
        return 84;
    port = atoi(av[1]);
    if (port == 0)
        return 84;
    server = create_server(port);
    if (server == NULL)
        return 84;
    process(server);
    destroy_server(server);
    return 0;
}
