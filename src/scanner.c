#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "scanner.h"

extern pthread_mutex_t log_mutex;

void* scan_ports(void* arg) {
    scan_range_t *range = (scan_range_t *)arg;

    for (int port = range->start_port; port <= range->end_port; port++) {
        // 1. Create the Socket
        // AF_INET: IPv4 | SOCK_STREAM: TCP | 0: Default Protocol (IP)
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) continue; 

        // 2. Define Target Address
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port); // htons: Host-to-Network Short (Endians)
        serv_addr.sin_addr.s_addr = inet_addr(range->ip);

        // 3. Attempt Connection
        // If connect returns 0, the port is open and accepting TCP handshakes
        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0) {
            
            // 4. Thread-Safe Logging
            pthread_mutex_lock(&log_mutex);
            printf("[+] Port %d is OPEN\n", port);
            pthread_mutex_unlock(&log_mutex);
        }

        // 5. Cleanup
        close(sock);
    }
    return NULL;
}
