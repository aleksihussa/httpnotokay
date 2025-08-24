#ifndef LISTENER_H
#define LISTENER_H

#include <sys/types.h>

/**
 * Create a TCP/IPv4 listening socket on the given port.
 * Returns the listening fd on success, or -1 on failure (errno set).
 */
int initialize_listener(int port, int backlog);

#endif /* LISTENER_H */
