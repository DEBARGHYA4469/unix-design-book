#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int sd, ns;
    struct sockaddr_un addr;
    socklen_t fromlen;
    char buf[256];
    const char *socket_path = "/tmp/ux_socket-1"; // Choose a path for your socket

    // Create socket
    sd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sd == -1) {
        perror("socket failed");
        return 1;
    }

    // Prepare the sockaddr_un structure
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);
    addr.sun_path[sizeof(addr.sun_path) - 1] = '\0'; // Ensure null termination
    fromlen = sizeof(struct sockaddr_un);

    // Bind the socket to the path
    if (bind(sd, (const struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("bind failed");
        close(sd);
        return 1;
    }

    // Listen for connections
    if (listen(sd, 1) == -1) {
        perror("listen failed");
        close(sd);
        unlink(socket_path); // Clean up the socket file
        return 1;
    }

    printf("Server listening on %s\n", socket_path);

    for (;;) {
        ns = accept(sd, (struct sockaddr *)&addr, &fromlen);
        if (ns > 0) {
            printf("sleep \n");
            close(ns);
        } else {
            perror("accept failed\n");
        }
        // close(ns); // You were closing ns twice, which is unnecessary
    }

    close(sd);
    unlink(socket_path); // Clean up the socket file when the server exits
    return 0;
}
