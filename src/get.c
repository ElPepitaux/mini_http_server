/*
** EPITECH PROJECT, 2024
** mini_http_server
** File description:
** get
*/

#include "server.h"

int openFIle(server_t *server, char *path)
{
    int fd = 0;
    fd = open(path, O_RDONLY);
    if (fd == -1)
        send(server->clients->socket, "HTTP/1.0 404 File not found\r\n", 30, 0);
    return fd;
}

bool errorFile(server_t *server, struct stat *st, char *path)
{
    if (stat(path, st) == -1) {
        free(path);
        send(server->clients->socket, "HTTP/1.0 404 Can't stat the file\n", 34, 0);
        return true;
    }
    if (S_ISDIR(st->st_mode)) {
        free(path);
        send(server->clients->socket, "HTTP/1.0 404 Is a directory\n", 28, 0);
        return true;
    }
    return false;
}

void sendHeader(server_t *server, const char *content, const char *type)
{
    char *Header = NULL;
    int size = snprintf(Header, 0, "HTTP/1.0 200 OK\nContent-type: %s\nContent-Length: %d\n\n%s", type, (int)strlen(content), content);
    Header = malloc(sizeof(char) * (size + 1));
    if (Header == NULL)
        return;
    sprintf(Header, "HTTP/1.0 200 OK\nContent-type: %s\nContent-Length: %d\n\n%s", type, (int)strlen(content), content);
    send(server->clients->socket, Header, strlen(Header), 0);
    free(Header);
}

void getFile(server_t *server, char *buffer)
{
    char *path = NULL;
    char *content = NULL;
    char *file = strtok(buffer, " ");
    int fd = 0;
    struct stat st;
    file = strtok(NULL, " ");
    path = malloc(sizeof(char) * (strlen(file) + 19));
    if (path == NULL)
        return;
    strcpy(path, "./server_root_dir");
    strcat(path, file);
    printf("Data received: \"GET %s\"\n", path);
    fd = openFIle(server, path);
    if (fd == -1)
        return;
    if (errorFile(server, &st, path))
        return;
    content = malloc(sizeof(char) * (st.st_size + 1));
    if (content == NULL)
        return;
    read(fd, content, st.st_size);
    printf("Reading content of %s: \"%s\", lenght: %d\n", path, content, (int)strlen(content));
    sendHeader(server, content, "application/octet-stream");
    free(path);
    close(fd);
    free(content);
}
