#include "../include/listener.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_PORT 8080

#define MAX_PENDING_CONNECTIONS 128

int main(void) {
  int listener_fd = initialize_listener(SERVER_PORT, MAX_PENDING_CONNECTIONS);

  for (;;) {
    pause();
  }
}
