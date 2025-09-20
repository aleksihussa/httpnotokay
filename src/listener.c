#include "../include/listener.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int initialize_listener(int port, int backlog) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd == -1) {
    perror("socket");
    return EXIT_FAILURE;
  }

  int reuse_socket_opt = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_socket_opt,
                 sizeof(reuse_socket_opt)) < 0) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(port);

  // Bind the socket to the specified port
  if (bind(socket_fd, (struct sockaddr *)&server_address,
           sizeof(server_address)) < 0) {
    perror("bind");
    close(socket_fd);
    exit(EXIT_FAILURE);
  }

  // Start listening for incoming connections
  if (listen(socket_fd, backlog) < 0) {
    perror("listen");
    close(socket_fd);
    exit(EXIT_FAILURE);
  }

  printf("Initiated a listening socker on port: %d...\n", port);
  return socket_fd;
}
