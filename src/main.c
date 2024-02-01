/*
** EPITECH PROJECT, 2024
** mini_http_server
** File description:
** main
*/

#include "server.h"

void My_strlen_server(server_t *server, char *buffer)
{
    char *str = NULL;
    int len = 0;

    printf("Data received: \"%s\"\n", buffer);
    len = snprintf(str, 0, "The length of \"%s\" is %d", buffer, (int)strlen(buffer));
    str = malloc(sizeof(char) * (len + 1));
    sprintf(str, "The length of \"%s\" is %d", buffer, (int)strlen(buffer));
    sendHeader(server, str, "application/octet-stream");
    free(str);
}

void process(server_t *server)
{
    char buffer[1024] = {0};
    char *request = NULL;
    char cpy[1024] = {0};
    if (read(server->clients->socket, buffer, 1024) <= 0)
        return;
    printf("|%s|\n", buffer);
    strcpy(cpy, buffer);
    request = strtok(cpy, " ");
    if (strcmp(request, "GET") == 0 || strcmp(request, "HEAD") == 0)
        getFile(server, buffer);
    else
        My_strlen_server(server, buffer);
}

int main(int ac, char **av)
{
    server_t server;
    if (ac != 2)
        return 84;
    server.port = atoi(av[1]);
    if (server.port == 0)
        return 84;
    if (create_connection(&server))
        return 84;
    process(&server);
    destroy_server(&server);
    return 0;
}
