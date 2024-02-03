// /*
// ** EPITECH PROJECT, 2024
// ** mini_http_server
// ** File description:
// ** get
// */

#include "server.h"

int openFIle(client_t *client, char *path)
{
    int fd = 0;
    fd = open(path, O_RDONLY);
    if (fd == -1)
        send(client->socket, "HTTP/1.0 404 File not found\r\n", 30, 0);
    return fd;
}

bool errorFile(client_t *client, struct stat *st, char *path)
{
    if (stat(path, st) == -1) {
        free(path);
        send(client->socket, "HTTP/1.0 404 Can't stat the file\n", 34, 0);
        return true;
    }
    if (S_ISDIR(st->st_mode)) {
        free(path);
        send(client->socket, "HTTP/1.0 404 Is a directory\n", 28, 0);
        return true;
    }
    return false;
}

void sendHeader(client_t *client, const char *content, const char *type)
{
    char *Header = NULL;
    int size = snprintf(Header, 0, "HTTP/1.0 200 OK\nContent-type: %s\nContent-Length: %d\n\n%s\n", type, (int)strlen(content), content);
    Header = malloc(sizeof(char) * (size + 1));
    if (Header == NULL)
        return;
    sprintf(Header, "HTTP/1.0 200 OK\nContent-type: %s\nContent-Length: %d\n\n%s\n", type, (int)strlen(content), content);
    send(client->socket, Header, strlen(Header), 0);
    free(Header);
}

char *excuteFile(char *path)
{
    char *params = strtok(NULL, " ?");
    char *value = NULL;
    char *key = NULL;
    char *buffer = NULL;

    while (params != NULL) {
        key = strtok(params, "=");
        value = strtok(NULL, "&");
        if (value == NULL)
            value = "";
        setenv(key, value, 1);
        params = strtok(NULL, " ?");
    }

    // i need to put the result of the execv in a buffer and send it to the client
    pid_t pid = 0;
    int pipefd[2];
    pipe(pipefd);
    pid = fork();
    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        execv(path, environ);
    }
    close(pipefd[1]);
    buffer = malloc(sizeof(char) * 100000);
    if (buffer == NULL)
        return NULL;
    read(pipefd[0], buffer, 100000);
    buffer[strlen(buffer)] = '\0';
    close(pipefd[0]);


    return buffer;
}

char *getFIleContent(int fd, struct stat *st)
{
    char *content = malloc(sizeof(char) * (st->st_size + 1));
    if (content == NULL)
        return NULL;
    read(fd, content, st->st_size);
    content[st->st_size] = '\0';
    return content;
}

void getMethode(client_t *client, char *buffer)
{
    char *path = NULL;
    char *content = NULL;
    char *file = strtok(buffer, " ");
    int fd = 0;
    struct stat st;
    file = strtok(NULL, " ?");
    path = malloc(sizeof(char) * (strlen(file) + 20));
    if (path == NULL)
        return;
    strcpy(path, "./server_root_dir");
    strcat(path, file);
    printf("Data received: \"GET %s\"\n", path);
    fd = openFIle(client, path);
    if (fd == -1)
        return;
    if (errorFile(client, &st, path))
        return;
    if (st.st_mode & S_IXUSR) {
        content = excuteFile(path);
    } else {
        content = getFIleContent(fd, &st);
    }
    printf("Reading content of %s: \"%s\", lenght: %d\n", path, content, (int)strlen(content));
    sendHeader(client, content, "application/octet-stream");
    free(path);
    close(fd);
    free(content);
}
