/*
** EPITECH PROJECT, 2024
** mini_http_server
** File description:
** main
*/

#include "server.h"

bool create_connection(int port)
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in peer_adress;
    peer_adress.sin_addr.s_addr = INADDR_ANY;
    peer_adress.sin_family = AF_INET;
    peer_adress.sin_port = htons(port);
    int opt = 1;
    int peer_adress_len = sizeof(peer_adress);
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("SETSOCKET FAILED\n");
        exit(84);
    }
    if (bind(s, (struct sockaddr*)&peer_adress, sizeof(peer_adress)) < 0) {
        perror("FAILED TO BIND\n");
        exit(84);
    }
    printf("Listening on port %d.\n", port);
    if (listen(s, SOMAXCONN) == -1) {
        perror("FAILED TO LISTEN\n");
        exit(84);
    }
    if ((accept(s, (struct sockaddr*)&peer_adress, (socklen_t *)&peer_adress_len)) < 0) {
        perror("CONNECTION FAILED\n");
        exit(84);
    }
    printf("Client connected ! IP: %s Port: %d\n", inet_ntoa(peer_adress.sin_addr), ntohs(peer_adress.sin_port));
    return 0;
}

int main(int ac, char **av)
{
    int port = 0;
    if (ac != 2)
        return 84;
    port = atoi(av[1]);
    if (port == 0)
        return 84;
    if (create_connection(port))
        return 84;
    return 0;
}
