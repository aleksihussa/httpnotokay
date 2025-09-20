#include "../include/listener.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 8081

#define MAX_PENDING_CONNECTIONS 128

int main(void) {
  int listener_fd = initialize_listener(SERVER_PORT, MAX_PENDING_CONNECTIONS);

  for (;;) {
    // Initialize client address structure for kernel to fill
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);

    // Accept an incoming connection
    int connection_fd =
        accept(listener_fd, (struct sockaddr *)&client_addr, &addrlen);

    if (connection_fd == -1) {
      perror("accept");
      continue;
    }
    // Buffer for incoming request
    char buffer[8192];
    ssize_t n = read(connection_fd, buffer, sizeof(buffer) - 1);

    if (n < 0) {
      perror("read");
      close(connection_fd);
      continue;
    }

    buffer[n] = '\0'; // null-terminate for safe printing
    printf("Received request:\n%s\n", buffer);

    // (Very naive) parse the first line to get method + path
    char method[16], path[256], version[16];
    if (sscanf(buffer, "%15s %255s %15s", method, path, version) == 3) {
      printf("Method: %s, Path: %s, Version: %s\n", method, path, version);
    }

    // Always send some response back
    const char *body = "Hello from httpnotokay!\n";
    char response[1024];
    int resp_len = snprintf(response, sizeof(response),
                            "HTTP/1.1 200 OK\r\n"
                            "Content-Length: %zu\r\n"
                            "Content-Type: text/plain\r\n"
                            "Connection: close\r\n"
                            "\r\n"
                            "%s",
                            strlen(body), body);

    if (write(connection_fd, response, resp_len) == -1) {
      perror("write");
    }
    close(connection_fd);
  }
}
